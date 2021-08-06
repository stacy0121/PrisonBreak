// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	// pawn 객체가 유효하면
	if (::IsValid(Pawn)) {
		// 속력 구해서 변수에 저장
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}

	auto Character = Cast<ACharacter>(Pawn);
	if (Character) {
		// 현재 이동 속도 저장
		CurrentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed();
	}
}
