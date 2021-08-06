// Fill out your copyright notice in the Description page of Project Settings.



#include "AIController.h"
#include "CoreMinimal.h"
#include "EnemyAIController.h"
#include <EngineUtils.h>
#include "Enemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"




void AEnemyAIController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{

	//Super::TickActor();

	//목차(뼈대)를 작성
	switch (m_state)
	{
	case EEnemyState::Idle:
		Idlestate();
		break;
	case EEnemyState::Move:
		Movestate();
		break;
	case EEnemyState::Check:
		Checkstate();
		break;
		//case EEnemyState::Attack:
			//Attackstate();
			//break;
	case EEnemyState::End:
		Endstate();
		break;
	}
}
//일정시간 기다리다가 상태를 move로 바꿔주자
//필요속성 : 기다릴 시간, 경과 시간
//일정 거리 내 있는 플레이어가 있다면 Checkstate로 바꿈
void AEnemyAIController::Idlestate()
{

	FString str = TEXT("Idle");
	//일정시간동안 기다리다가 상태를 Move로 바꿔주자
	//1. 시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. 대기시간이 다 됐으니까]
	if (currentTime > idleDelayTime)
	{	//3. 상태를 Move로 바꿔주자.

		m_state = EEnemyState::Move;
		currentTime = 0;
		//타겟포인트를 랜덤하게 왕복한다.
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();
	}
}
//target point를 랜덤하게 왕복한다
//만약 일정 거리 내에 있는 플레이어가 있다면 Checkstate로 바꿈
//필요속성 :  플레이어와의 거리
void AEnemyAIController::Movestate()
{	// 만약 일정 거리 내에 있는 플레이어가 있다면 Checkstate로 바꿈
	//필요속성:check 범위
	//1. 일정거리 내에 플레이어가 있다면
		//player와 enemy의 거리
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	//FVector direction = Ptarget->GetActorLocation(); - me->GetActorLocation();
	FVector direction = playerCharacter->GetActorLocation(); - me->GetActorLocation();
	float distance = direction.Size();
	//2. Checkstate 로 바꿈

	if (checkRange > distance)
	{
		m_state = EEnemyState::Check;


	}
	else 
	{
	//아니라면 idle로 바꿈
		m_state = EEnemyState::Idle;
	
	}

}
//만약 door의 상태가 철창떼기가 아니라면 Idle로 바꿈
// 필요속성 : 타겟 플레이어 상태
//플레이어의 상태가 철창떼기라면 Endstate로 바꿈
void AEnemyAIController::Checkstate()
{
	//door 상태가 철창떼기라면 Endstate로 바꿈

	
	//if(isCutting)
	//{
	//	m_state = EEnemyState::End;


	//}
	// 철창떼기 아니라면 idle로 바꿈
	/*else*/
	//{
		//m_state = EEnemyState::Idle;
	//}
	

}

void AEnemyAIController::Endstate()
{

}





ATargetPoint* AEnemyAIController::GetRandomWaypoint()
{
//랜덤하게 포인트 변경
auto index = FMath::RandRange(0, Waypoints.Num()-1);
return Cast<ATargetPoint>(Waypoints[index]);
}

void AEnemyAIController::GoToRandomWaypoint()
{
	//랜덤 포인트 이동
	MoveToActor(GetRandomWaypoint());
}

