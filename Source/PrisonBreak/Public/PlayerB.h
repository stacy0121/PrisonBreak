// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerB.generated.h"

UENUM(BlueprintType)
enum class EPlayerBState : uint8
{
	B_CanLock UMETA(DisplayName = "B_CANLOCK_STATE"),
	B_Locking UMETA(DisplayName = "B_LOCKING_STATE"),
	B_CanWatch UMETA(DisplayName = "B_CANWATCH_STATE"),
	B_Talk UMETA(DisplayName = "B_TALK_STATE"),
	B_End UMETA(DisplayName = "B_END_STATE")
};
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
	UFUNCTION(BlueprintCallable, Category = "Code")
	void MoveForward(float value);

	UFUNCTION(BlueprintCallable, Category = "Code")
		void Turn(float value);

	UFUNCTION(BlueprintCallable, Category = "Code")
	void B_OnInteract();

	UFUNCTION(BlueprintCallable, Category = "Code")
		void B_DeInteract();

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

	// 플레이어가 문 앞에 섰는지 안섰는지 체크
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool bIsInTrigger;
	
	// 문 여는 게이지
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = State)
	float bCuttingTime;

	// 문 여는 게이지가 얼마나 차야 하는지
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = State)
	float bCuttingTimeMax = 5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Target")
		class APlayerA* playerA;

	// 달리기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// 플레이어 상태머신
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPlayerBState bState = EPlayerBState::B_CanWatch;

	void B_CanWatch();
	void B_Talk();
	void B_CanLock();
	void B_Locking();
	void B_End();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* M_guard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* M_talking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* M_escape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		UAnimMontage* M_idle;
};
