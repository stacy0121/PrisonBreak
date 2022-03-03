// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Enemy.h"
#include "EnemyAnimInstance.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

 //����� ���¸� ����

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Talk,
	Check,
	End

};

UCLASS()
class PRISONBREAK_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()




virtual void BeginPlay() override;
// Called every frame

virtual void TickActor(float DeltaTime,enum ELevelTick TickType,FActorTickFunction& ThisTickFunction) override;
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSM")
		EEnemyState m_state;

	//�ʿ�Ӽ� : ��ٸ� �ð�, ��� �ð�
	UPROPERTY(EditAnywhere, Category = FSM)
		float idleDelayTime = 4;

	UPROPERTY()
		float currentTime = 0;

	//talk �õ��� ���� �÷��̾� A�� enemy�� ���ֺ��� ���ִ� �ð�
	UPROPERTY()
		float CheckTime = 6;

	//talk�� state ���� ��  idle�� �ٲ����� ��ٸ� �ð�
	UPROPERTY()
		float talkTime = 5;


	UPROPERTY(EditAnywhere, Category = Target)
		class APlayerA* targetA;

	UPROPERTY(EditAnywhere, Category = Target)
		class APlayerB* targetB;

	UPROPERTY()
		class AEnemy* me;

	//UPROPERTY(EditAnywhere, Category = FSM)
		//class APPlayer* Ptarget;

	//�ʿ�Ӽ� : check ����
	//UPROPERTY(EditAnywhere, Category = FSM)
	//	float checkRange = 400;

	

	//Enemy �� ����ϰ� �ִ� Animation Instance ���
	//UPROPERTY()
		//class UEnemyAnimInstance* anim;


	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundBase* endSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundBase* talkSound;

private:

	void Idlestate();
	void Movestate();
	void Talkstate();
	void Checkstate();
	void Endstate();


private:


	UPROPERTY()
		TArray<AActor*> Waypoints;

	UFUNCTION()
		ATargetPoint* GetRandomWaypoint();

	UFUNCTION()
		void GoToRandomWaypoint();

	FTimerHandle TimerHandle;

	UFUNCTION()
		ATargetPoint* WaypointA();

	UFUNCTION()
		ATargetPoint* WaypointB();



};
