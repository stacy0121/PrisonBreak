// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerB.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Door.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerA.h"
#include "PrisonBreak.h"


// Sets default values
APlayerB::APlayerB()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �ε巯�� ������
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// ��������
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 300.0f;
	BoomArm->bUsePawnControlRotation = true;

	// ī�޶�
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeLocationAndRotation(FVector(-12, 0, 146), FRotator(0, -20, 0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("SkeletalMesh'/Game/Character/PlayerB.PlayerB'"));

	if (SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	// �ִϸ��̼� ��� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �ִϸ��̼� �������Ʈ Ŭ���� ��������
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/Blueprint/PB_AnimBlueprint.PB_AnimBlueprint_C'"));
	if (PlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	}

	// �ȴ� �ӵ�
	UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementPtr->MaxWalkSpeed = 300;

	// �� �� �ӵ� 2��
	SprintSpeedMultiplier = 2.0f;
}

// Called when the game starts or when spawned
void APlayerB::BeginPlay()
{
	Super::BeginPlay();

	playerA = Cast<APlayerA>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerA::StaticClass()));
}

// Called every frame
void APlayerB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (bState)
	{
 	case EPlayerBState::B_CanLock:
 		B_CanLock();
 		break;
 	case EPlayerBState::B_Locking:
 		B_Locking();
 		break;
	case EPlayerBState::B_CanWatch:
		B_CanWatch();
		break;
	case EPlayerBState::B_Talk:
		B_Talk();
		break;
	case EPlayerBState::B_End:
		B_End();
		break;
	}
}

// Called to bind functionality to input
void APlayerB::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("PlayerBMoveForward", this, &APlayerB::MoveForward);
	PlayerInputComponent->BindAxis("PlayerBTurn", this, &APlayerB::Turn);

	PlayerInputComponent->BindAction("PlayerBRun", IE_Pressed, this, &APlayerB::Sprint);
	PlayerInputComponent->BindAction("PlayerBRun", IE_Released, this, &APlayerB::StopSprinting);
}

void APlayerB::MoveForward(float value)
{
	if (Controller != NULL && value != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ���
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void APlayerB::Turn(float value)
{
	if (value != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddYawInput(value);
	}
}

// �÷��̾ ��ȣ�ۿ� Ű�� ������ ��
void APlayerB::B_OnInteract()
{
	if (bIsInTrigger == true && bState == EPlayerBState::B_CanLock )
	{
		CALLINFO();
		bState = EPlayerBState::B_Locking;
	}

	if (bIsInTrigger == true && bState == EPlayerBState::B_CanWatch)
	{
		bState = EPlayerBState::B_Talk;
	}
}

// �÷��̾ ��ȣ�ۿ� Ű�� ���� ��
void APlayerB::B_DeInteract()
{
	if (bIsInTrigger == true && bState == EPlayerBState::B_Locking && bCuttingTime < bCuttingTimeMax)
	{
		bState = EPlayerBState::B_CanLock;
	}
}

// �޸���
void APlayerB::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void APlayerB::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

// �÷��̾ ���� �� �� �ִ� ����
void APlayerB::B_CanLock()
{
	if (M_idle) {
		PlayAnimMontage(M_idle, 1, NAME_None);
	}
}

// �÷��̾ ���� ���� �� �� ����
void APlayerB::B_Locking()
{
	bCuttingTime += GetWorld()->DeltaTimeSeconds;

	// Ż�� �ִϸ��̼� ����
	if (M_escape) {
		PlayAnimMontage(M_escape, 1, NAME_None);
	}

	if (bCuttingTime > bCuttingTimeMax)
	{
		bState = EPlayerBState::B_End;
	}
}

// �÷��̾ ���� ���ų� ��ȭ�� �� �� �ִ� ����
void APlayerB::B_CanWatch()
{
	if (playerA->lockComplete == true)
	{
		bState = EPlayerBState::B_CanLock;
	}
}

// �÷��̾ �������� ��ȭ�ϴ� ����
void APlayerB::B_Talk()
{
	if (M_talking) {
		PlayAnimMontage(M_talking, 1, NAME_None);
	}
}

void APlayerB::B_End()
{
	if (M_idle) {
		PlayAnimMontage(M_idle, 1, NAME_None);
	}
}