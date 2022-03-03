// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerA.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PrisonBreak.h"
#include "Door.h"
#include "CCTV.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerA::APlayerA()
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

	// �ٵ� �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("SkeletalMesh'/Game/Character/PlayerA.PlayerA'"));
	if (SK_BODY.Succeeded())
	{
		// ĳ���Ϳ��� ��ӵ� �޽ÿ� ���̷�Ż �޽� ����
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	// �ִϸ��̼� ��� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// �ִϸ��̼� �������Ʈ Ŭ���� ��������
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/Blueprint/PA_AnimBlueprint.PA_AnimBlueprint_C'"));
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
void APlayerA::BeginPlay()
{
	Super::BeginPlay();
	
	target = UGameplayStatics::GetActorOfClass(GetWorld(), ADoor::StaticClass());
}

// Called every frame
void APlayerA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (aState)
	{
	case EPlayerAState::CanLock:
		CanLock();
		break;
	case EPlayerAState::Locking:
		Locking();
		break;
	case EPlayerAState::CanWatch:
		CanWatch();
		break;
	case EPlayerAState::Talk:
		Talk();
		break;
	}

}

// Called to bind functionality to input
void APlayerA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerA::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerA::Sprint);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerA::StopSprinting);

	// �÷��̾� ��ȣ�ۿ� Ű ���ε�
	PlayerInputComponent->BindAction("PlayerAInteract", IE_Pressed, this, &APlayerA::OnInteraction);
	PlayerInputComponent->BindAction("PlayerAInteract", IE_Released, this, &APlayerA::DeInteraction);
}

// ���� �� �տ� �ְ� ���� �� �� �ִ� ���� �� ��
// F Ű�� ������ ���� ���� ���°� �ȴ�.
void APlayerA::OnInteraction()
{
	if ( isInTrigger == true && aState == EPlayerAState::CanLock)
	{
		CALLINFO();
		aState = EPlayerAState::Locking;
	}

	   if (isInTrigger == true && aState == EPlayerAState::CanWatch)
   {
      aState = EPlayerAState::Talk;
   }
}

// ���� ���� �� ���� �ʾ�����
// F Ű�� ���� ���� �� �� �ִ� ���°� �ȴ�.
void APlayerA::DeInteraction()
{
	if (isInTrigger == true && aState == EPlayerAState::Locking && cuttingTime < cuttingComplete)
	{
		CALLINFO();
		aState = EPlayerAState::CanLock;
	}
}

// �޸���
void APlayerA::Sprint()
{
	// �ȴ� �ӵ����� 2��
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void APlayerA::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

void APlayerA::MoveForward(float value)
{
	if (Controller != NULL && value != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		// ��� ���� �������� �˾Ƴ���, �÷��̾ �� �������� �̵��ϰ��� �Ѵٰ� ���
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

void APlayerA::CanWatch()
{
	if (M_idle) {
		PlayAnimMontage(M_idle, 1, NAME_None);
	}
}

// �÷��̾ ���� �� �� �ִ� ����
void APlayerA::CanLock()
{
	if (M_idle) {
		PlayAnimMontage(M_idle, 1, NAME_None);
	}
}

// �÷��̾ ���� ���� �� �� ����
void APlayerA::Locking()
{
	cuttingTime += GetWorld()->DeltaTimeSeconds;
	PRINTLOG(TEXT("%f"), cuttingTime);

	if (cuttingTime / 0.5f == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), unlockSound);
	}

	// Ż�� �ִϸ��̼� ����
	if (M_escape) {
		PlayAnimMontage(M_escape, 1, NAME_None);
	}

	// ���� ���� �� �����ٸ� ���� �� �� �ִ� ���°� �ȴ�. 
	if (cuttingTime > cuttingComplete)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), unlockCompleteSound);
		lockComplete = true;
		aState = EPlayerAState::CanWatch;
	}
}

// �÷��̾ �������� ��ȭ�ϴ� ����
void APlayerA::Talk()
{
	if (M_talking) {
		PlayAnimMontage(M_talking, 1, NAME_None);
	}
}