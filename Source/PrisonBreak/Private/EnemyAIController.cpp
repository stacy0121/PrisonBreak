// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include <AIController.h>
#include <EngineUtils.h>
#include "Enemy.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerA.h"
#include "PlayerB.h"
#include "GameFramework/Character.h"
#include "PrisonBreak.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

/*	anim = Cast<UEnemyAnimInstance>(me->GetMesh()->GetAnimInstance());*/

	me = Cast<AEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), AEnemy::StaticClass()));
		
	targetA = Cast<APlayerA>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerA::StaticClass()));
	targetB = Cast<APlayerB>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerB::StaticClass()));



}

void AEnemyAIController::TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{

	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	//목차(뼈대)를 작성
	switch (m_state)
	{
	case EEnemyState::Idle:
		Idlestate();
		break;
	case EEnemyState::Move:
		Movestate();
		break;
	case EEnemyState::Talk:
		Talkstate();
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
	CALLINFO();
	

	//=============================================== idle  >> check >>>
	// 
	//enemy가 문앞 triggerA(A앞) 박스에 진입 시 enemy가 문앞에 있다면 
//  tagetpoint0(A의 감옥앞) 으로 이동한 뒤 Check 상태로
	if (me->inEnemyTriggerA == true && targetA->isInTrigger == true)
	{

		CALLINFO();

		m_state = EEnemyState::Check;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointA());


	}

	//enemy가 문앞 triggerB(B앞) 박스에 진입 시 check state로 바꿈
	// tagetpoint1(B의 감옥앞) 으로 이동한 뒤 Check 상태로
	if (me->inEnemyTriggerB == true && targetB->bIsInTrigger == true)
	{
		CALLINFO();

		m_state = EEnemyState::Check;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointB());

	}

	//=============================================== idle  >> Move >>>
	//일정시간동안 기다리다가 상태를 Move로 바꿔주자
	//1. 시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. 대기시간이 다 됐으니까]
	if (currentTime > idleDelayTime)
	{	//3. 상태를 Move로 바꿔주자.

		m_state = EEnemyState::Move;
		currentTime = 0;
		//타겟포인트를 랜덤하게 이동한다.
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();

	}
}

//enemy가 감옥 앞 trigger박스에 진입하고
//플레이어A,B가 문 앞 trigger box 에 진입한다면 
// enemy가 감옥 문 앞 trigger point로 이동하고
//Checkstate로 바꿈
void AEnemyAIController::Movestate()
{
	targetB = Cast<APlayerB>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerB::StaticClass()));
	CALLINFO();

	//=============================================== Move  >> Check >>>	
	//enemy가 문앞 triggerA(A앞) 박스에 진입 시 enemy가 문앞에 있다면 
//  tagetpoint0(A의 감옥앞) 으로 이동한 뒤 Check 상태로
	if (me->inEnemyTriggerA == true && targetA->isInTrigger == true)
	{

		CALLINFO();
		
		m_state = EEnemyState::Check;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointA());

		
	}

	//enemy가 문앞 triggerB(B앞) 박스에 진입 시 check state로 바꿈
	// tagetpoint1(B의 감옥앞) 으로 이동한 뒤 Check 상태로
	if (me->inEnemyTriggerB == true && targetB->bIsInTrigger == true)
	{
		CALLINFO();
		
		m_state = EEnemyState::Check;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointB());
		

	}

	//=============================================== Move  >> idle >>>	
	else
	{
		//전부 아니라면 idle로 바꿈
		m_state = EEnemyState::Idle;
	}


}
//enemy가 door트리거 박스 안에 있을 때 특정키 입력하면 
//그 입력을 받아서 talkstate로 변경
//대화가 끝나면 idlestate
//필요속성 : 플레이어의 트리거 박스 내 위치 여부, 
void AEnemyAIController::Talkstate()
{
// 대화소리 랜덤 재생

	CALLINFO();
	UGameplayStatics::PlaySound2D(GetWorld(), talkSound);

	

	currentTime += GetWorld()->DeltaTimeSeconds;

	//=============================================== Talk  >> idle >>>	
	//talk 시간이 지나면 idle로 전환
	if(currentTime > talkTime)
	{
	
		m_state = EEnemyState::Idle;
		currentTime = 0;
	
	
	}
}

//player가 대화를 원하는지 문열기를 시도하는지 감시하러 문앞에 오는 state
//만약 player의 상태가 Locking이라면 end로 바꿈
//만약 player의 상태가 Locking아니라면 Idle로 바꿈
// 필요속성 : 타겟 플레이어 상태

void AEnemyAIController::Checkstate()
{
	CALLINFO();
	currentTime += GetWorld()->DeltaTimeSeconds;
	//갸웃거리는 애니메이션 재생

//=============================================== Talk  >> idle >>>	
// 
	//만약 플레이어 A가 문을 여는 상태였다면>> 문앞이동>> 화내는 애니메이션 재생후 >>검거엔딩
	if (me->inEnemyTriggerA == true && targetA->aState == EPlayerAState::Locking)
	{
		
		m_state = EEnemyState::End;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointA());
	}

	//만약 플레이어 B가 문을 여는 상태였다면>> 문앞이동>> 화내는 애니메이션 재생후 >>검거엔딩
	if (me->inEnemyTriggerB == true && targetB->bState == EPlayerBState::B_Locking)
	{
		
		m_state = EEnemyState::End;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointB());
	}


	//만약 플레이어 A가 문을 여는 상태가 아니고 checktime 동안 멀뚱멀뚱 있다면
	//다른 랜덤 포인트로 이동 후 idle state로 바꾼다.
	if (targetA->aState != EPlayerAState::Locking && currentTime > CheckTime)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();
		currentTime = 0;

		m_state = EEnemyState::Idle;

	}
	//만약 플레이어 B가 문을 여는 상태가 아니고 checktime 동안 멀뚱멀뚱 있다면
	//다른 랜덤 포인트로 이동 후 idle state로 바꾼다.
	if (targetB->bState != EPlayerBState::B_Locking && currentTime > CheckTime)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();

		m_state = EEnemyState::Idle;
		currentTime = 0;
	}

	//만약 플레이어 A가 대화 요청을 한다면
	if (me->inEnemyTriggerA == true && targetA->aState == EPlayerAState::Talk)
	{
		//A가 대화 요청을 한다면 enemy도 Talk로 가서 말하는 것을 띄우자
		m_state = EEnemyState::Talk;
	}
	//만약 플레이어 B가 대화 요청을 한다면
	if (me->inEnemyTriggerB == true && targetB->bState == EPlayerBState::B_Talk)
	{
		m_state = EEnemyState::Talk;
	}
	else
	{
		m_state = EEnemyState::Idle;

	}

	

}

void AEnemyAIController::Endstate()
{
	CALLINFO();
	UGameplayStatics::PlaySound2D(GetWorld(), endSound);
	
	//엔딩 UI 출력
	//엔딩 애니메이션 
	
	UGameplayStatics::OpenLevel(this, "FailMap");

}


ATargetPoint* AEnemyAIController::GetRandomWaypoint()
{
//랜덤하게 포인트 변경
	CALLINFO();
auto index = FMath::RandRange(2, Waypoints.Num()-1);
return Cast<ATargetPoint>(Waypoints[index]);
}

void AEnemyAIController::GoToRandomWaypoint()
{
	CALLINFO();
	//랜덤 포인트 이동
	MoveToActor(GetRandomWaypoint());
}

ATargetPoint* AEnemyAIController::WaypointA()
{
	//A의 감옥문 앞
	auto index = FMath::RandRange(0, 0);
	return Cast<ATargetPoint>(Waypoints[index]);

}

ATargetPoint* AEnemyAIController::WaypointB()
{
	//B의 감옥문앞
	auto index = FMath::RandRange(1, 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

