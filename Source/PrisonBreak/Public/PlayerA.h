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

	// �̵� �Լ�
	void MoveForward(float value);

	// ��ȣ�ۿ� �Է� �Լ�
	void OnInteraction();
	void DeInteraction();

	// �޸���
	void Sprint();
	void StopSprinting();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ��������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* BoomArm;

	// ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	// �÷��̾ �� �տ� ������ �ȼ����� üũ
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool isInTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
		bool lockComplete;

	// �� ���� ������
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = State)
		float cuttingTime = 0;

	// �� ���� �������� �󸶳� ���� �ϴ���
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = State)
		float cuttingComplete = 5;

	UPROPERTY()
		class ADoor* door;

	UPROPERTY()
		class ACCTV* cctv;

	UPROPERTY(VisibleAnywhere, Category = "Target")
		class AActor* target;

	// �÷��̾ ���� ���� ���� �Ҹ�
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundBase* unlockSound;

	// �÷��̾ ���� �� ���� ���� �Ҹ�
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* unlockCompleteSound;

	// �޸���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
		float SprintSpeedMultiplier;

	// �÷��̾� ���¸ӽ�
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
