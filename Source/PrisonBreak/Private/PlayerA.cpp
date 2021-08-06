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

	// 바디 메시 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("SkeletalMesh'/Game/Character/PlayerA.PlayerA'"));
	if (SK_BODY.Succeeded())
	{
		// 캐릭터에서 상속된 메시에 스켈레탈 메시 설정
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	// 애니메이션 모드 설정
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	// 애니메이션 블루프린트 클래스 가져오기
	static ConstructorHelpers::FClassFinder<UAnimInstance> PlayerAnim(TEXT("AnimBlueprint'/Game/Blueprint/PA_AnimBlueprint.PA_AnimBlueprint_C'"));
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
void APlayerA::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (interact == 1 && isInTrigger == true)
	{
		cuttingComplete += DeltaTime + cuttingTime;
	}

	if (cuttingComplete> 3)
	{
		door = Cast<ADoor>(GetOwner());
		door->Destroy();
	}

	if (interactTwo == 1)
	{
		GetWorld()->GetFirstPlayerController()->UnPossess();
		if (GetWorld()->GetFirstPlayerController() == nullptr)
		{
			CALLINFO();
			cctv = Cast<ACCTV>(GetOwner());
			cctv->GetWorld()->GetFirstPlayerController()->Possess(cctv);
		}
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

	// 플레이어 상호작용 키 바인드
	PlayerInputComponent->BindAxis(TEXT("Interaction"), this, &APlayerA::OnInteraction);
	PlayerInputComponent->BindAxis(TEXT("InteractionTwo"), this, &APlayerA::OnInteractionTwo);
}


void APlayerA::OnInteraction(float value)
{
	if (Controller != NULL && value != 0.0)
	{
		interact = value;
	}
}

void APlayerA::OnInteractionTwo(float value)
{
	if (Controller != NULL && value != 0.0)
	{
		interactTwo = value;
	}
}

// 달리기
void APlayerA::Sprint()
{
	// 걷는 속도에서 2배
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void APlayerA::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

// 이동
void APlayerA::MoveForward(float value)
{
	if (Controller != NULL && value != 0.0) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, Rotation.Yaw, 0);
		// 어느 쪽이 전방인지 알아내어, 플레이어가 그 방향으로 이동하고자 한다고 기록
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, value);
	}
}