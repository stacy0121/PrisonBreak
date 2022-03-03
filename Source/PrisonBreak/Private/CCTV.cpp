// Fill out your copyright notice in the Description page of Project Settings.


#include "CCTV.h"

// Sets default values
ACCTV::ACCTV()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ACCTV::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCTV::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCTV::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("CCTVTurn", this, &APawn::AddControllerYawInput);
}

void ACCTV::Turn(float value)
{
	if (value != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);
		PC->AddYawInput(value);
	}
}

