// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRISONBREAK_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float CurrentWalkSpeed;
};
