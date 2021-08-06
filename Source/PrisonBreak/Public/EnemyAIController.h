// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Enemy.h"
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
	Check,
	End

};

UCLASS()
class PRISONBREAK_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()



// Called every frame

virtual void TickActor(float DeltaTime,enum ELevelTick TickType,FActorTickFunction& ThisTickFunction) override;
	
	public:
	UPROPERTY(EditAnywhere, Category = "FSM", BlueprintReadWrite)
		EEnemyState m_state;

	//필요속성 : 기다릴 시간, 경과 시간
	UPROPERTY(EditAnywhere, Category = FSM)
		float idleDelayTime = 3;

	UPROPERTY()
		float currentTime = 0;

	UPROPERTY()
		class AEnemy* me;

	//UPROPERTY(EditAnywhere, Category = FSM)
		//class APPlayer* Ptarget;

	//필요속성 : check 범위
	UPROPERTY(EditAnywhere, Category = FSM)
		float checkRange = 200;

	UPROPERTY()
		float CheckTime = 3;


private:

	void Idlestate();
	void Movestate();
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


};
