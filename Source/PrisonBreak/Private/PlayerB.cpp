// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerB.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlayerB::APlayerB()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 부드러운 움직임
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// 스프링암
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 300.0f;
	BoomArm->bUsePawnControlRotation = true;

	// 카메라
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeLocationAndRotation(FVector(-12, 0, 146), FRotator(0, -20, 0));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("SkeletalMesh'/Game/Character/PlayerB.PlayerB'"));

	if (SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	// 애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애니메이션 블루프린트 클래스 가져오기
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/Blueprint/PB_AnimBlueprint.PB_AnimBlueprint_C'"));
	if (PlayerAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(PlayerAnim.Class);
	}

	// 걷는 속도
	UCharacterMovementComponent* MovementPtr = Cast<UCharacterMovementComponent>(GetCharacterMovement());
	MovementPtr->MaxWalkSpeed = 300;

	// 뛸 때 속도 2배
	SprintSpeedMultiplier = 2.0f;
}

// Called when the game starts or when spawned
void APlayerB::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerB::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("PlayerBMoveForward", this, &APlayerB::MoveForward);
	PlayerInputComponent->BindAxis("PlayerBTurn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("PlayerBRun", IE_Pressed, this, &APlayerB::Sprint);
	PlayerInputComponent->BindAction("PlayerBRun", IE_Released, this, &APlayerB::StopSprinting);
}

// 이동
void APlayerB::MoveForward(float value)
{
	if (Controller != NULL && value != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}

// 달리기
void APlayerB::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void APlayerB::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}