// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerA.generated.h"

UENUM(BlueprintType)
enum class EPlayerAState : uint8
{
	CanLock UMETA(DisplayName = "CANLOCK_STATE"),
	Locking UMETA(DisplayName = "LOCKING_STATE"),
	CanWatch UMETA(DisplayName = "CANWATCH_STATE"),
	Talk UMETA(DisplayName = "TALK_STATE"),
};

UCLASS()
class PRISONBREAK_API APlayerA : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerA();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 이동 함수
	void MoveForward(float value);

	// 상호작용 입력 함수
	void OnInteraction();
	void DeInteraction();

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
		bool isInTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool lockComplete;

	// 문 여는 게이지
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = State)
		float cuttingTime = 0;

	// 문 여는 게이지가 얼마나 차야 하는지
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = State)
		float cuttingComplete = 5;

	UPROPERTY()
		class ADoor* door;

	UPROPERTY()
		class ACCTV* cctv;

	UPROPERTY(VisibleAnywhere, Category = "Target")
		class AActor* target;

	// 플레이어가 문을 열면 나는 소리
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundBase* unlockSound;

	// 플레이어가 문을 다 열면 나는 소리
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* unlockCompleteSound;

	// 달리기
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// 플레이어 상태머신
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EPlayerAState aState = EPlayerAState::CanLock;

	void CanWatch();
	void CanLock();
	void Locking();
	void Talk();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* M_escape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* M_idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* M_guard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	UAnimMontage* M_talking;
};
