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

 //사용할 상태를 정의

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

	//필요속성 : 기다릴 시간, 경과 시간
	UPROPERTY(EditAnywhere, Category = FSM)
		float idleDelayTime = 4;

	UPROPERTY()
		float currentTime = 0;

	//talk 시도를 위해 플레이어 A와 enemy가 마주보고 서있는 시간
	UPROPERTY()
		float CheckTime = 6;

	//talk로 state 변경 후  idle로 바뀌기까지 기다릴 시간
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

	//필요속성 : check 범위
	//UPROPERTY(EditAnywhere, Category = FSM)
	//	float checkRange = 400;

	

	//Enemy 가 사용하고 있는 Animation Instance 기억
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
