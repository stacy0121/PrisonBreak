// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerB.generated.h"

UCLASS()
class PRISONBREAK_API APlayerB : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerB();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 이동 함수
	void MoveForward(float value);
	void Turn(float value);

	// 달리기
	void Sprint();
	void StopSprinting();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 스프링암
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* BoomArm;

	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	// 달리기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;
};
