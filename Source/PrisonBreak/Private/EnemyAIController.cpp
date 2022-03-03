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

	//����(����)�� �ۼ�
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
//�����ð� ��ٸ��ٰ� ���¸� move�� �ٲ�����
//�ʿ�Ӽ� : ��ٸ� �ð�, ��� �ð�
//���� �Ÿ� �� �ִ� �÷��̾ �ִٸ� Checkstate�� �ٲ�
void AEnemyAIController::Idlestate()
{
	CALLINFO();
	

	//=============================================== idle  >> check >>>
	// 
	//enemy�� ���� triggerA(A��) �ڽ��� ���� �� enemy�� ���տ� �ִٸ� 
//  tagetpoint0(A�� ������) ���� �̵��� �� Check ���·�
	if (me->inEnemyTriggerA == true && targetA->isInTrigger == true)
	{

		CALLINFO();

		m_state = EEnemyState::Check;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointA());


	}

	//enemy�� ���� triggerB(B��) �ڽ��� ���� �� check state�� �ٲ�
	// tagetpoint1(B�� ������) ���� �̵��� �� Check ���·�
	if (me->inEnemyTriggerB == true && targetB->bIsInTrigger == true)
	{
		CALLINFO();

		m_state = EEnemyState::Check;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointB());

	}

	//=============================================== idle  >> Move >>>
	//�����ð����� ��ٸ��ٰ� ���¸� Move�� �ٲ�����
	//1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	//2. ���ð��� �� �����ϱ�]
	if (currentTime > idleDelayTime)
	{	//3. ���¸� Move�� �ٲ�����.

		m_state = EEnemyState::Move;
		currentTime = 0;
		//Ÿ������Ʈ�� �����ϰ� �̵��Ѵ�.
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();

	}
}

//enemy�� ���� �� trigger�ڽ��� �����ϰ�
//�÷��̾�A,B�� �� �� trigger box �� �����Ѵٸ� 
// enemy�� ���� �� �� trigger point�� �̵��ϰ�
//Checkstate�� �ٲ�
void AEnemyAIController::Movestate()
{
	targetB = Cast<APlayerB>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerB::StaticClass()));
	CALLINFO();

	//=============================================== Move  >> Check >>>	
	//enemy�� ���� triggerA(A��) �ڽ��� ���� �� enemy�� ���տ� �ִٸ� 
//  tagetpoint0(A�� ������) ���� �̵��� �� Check ���·�
	if (me->inEnemyTriggerA == true && targetA->isInTrigger == true)
	{

		CALLINFO();
		
		m_state = EEnemyState::Check;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointA());

		
	}

	//enemy�� ���� triggerB(B��) �ڽ��� ���� �� check state�� �ٲ�
	// tagetpoint1(B�� ������) ���� �̵��� �� Check ���·�
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
		//���� �ƴ϶�� idle�� �ٲ�
		m_state = EEnemyState::Idle;
	}


}
//enemy�� doorƮ���� �ڽ� �ȿ� ���� �� Ư��Ű �Է��ϸ� 
//�� �Է��� �޾Ƽ� talkstate�� ����
//��ȭ�� ������ idlestate
//�ʿ�Ӽ� : �÷��̾��� Ʈ���� �ڽ� �� ��ġ ����, 
void AEnemyAIController::Talkstate()
{
// ��ȭ�Ҹ� ���� ���

	CALLINFO();
	UGameplayStatics::PlaySound2D(GetWorld(), talkSound);

	

	currentTime += GetWorld()->DeltaTimeSeconds;

	//=============================================== Talk  >> idle >>>	
	//talk �ð��� ������ idle�� ��ȯ
	if(currentTime > talkTime)
	{
	
		m_state = EEnemyState::Idle;
		currentTime = 0;
	
	
	}
}

//player�� ��ȭ�� ���ϴ��� �����⸦ �õ��ϴ��� �����Ϸ� ���տ� ���� state
//���� player�� ���°� Locking�̶�� end�� �ٲ�
//���� player�� ���°� Locking�ƴ϶�� Idle�� �ٲ�
// �ʿ�Ӽ� : Ÿ�� �÷��̾� ����

void AEnemyAIController::Checkstate()
{
	CALLINFO();
	currentTime += GetWorld()->DeltaTimeSeconds;
	//�����Ÿ��� �ִϸ��̼� ���

//=============================================== Talk  >> idle >>>	
// 
	//���� �÷��̾� A�� ���� ���� ���¿��ٸ�>> �����̵�>> ȭ���� �ִϸ��̼� ����� >>�˰ſ���
	if (me->inEnemyTriggerA == true && targetA->aState == EPlayerAState::Locking)
	{
		
		m_state = EEnemyState::End;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointA());
	}

	//���� �÷��̾� B�� ���� ���� ���¿��ٸ�>> �����̵�>> ȭ���� �ִϸ��̼� ����� >>�˰ſ���
	if (me->inEnemyTriggerB == true && targetB->bState == EPlayerBState::B_Locking)
	{
		
		m_state = EEnemyState::End;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		MoveToActor(WaypointB());
	}


	//���� �÷��̾� A�� ���� ���� ���°� �ƴϰ� checktime ���� �ֶ׸ֶ� �ִٸ�
	//�ٸ� ���� ����Ʈ�� �̵� �� idle state�� �ٲ۴�.
	if (targetA->aState != EPlayerAState::Locking && currentTime > CheckTime)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();
		currentTime = 0;

		m_state = EEnemyState::Idle;

	}
	//���� �÷��̾� B�� ���� ���� ���°� �ƴϰ� checktime ���� �ֶ׸ֶ� �ִٸ�
	//�ٸ� ���� ����Ʈ�� �̵� �� idle state�� �ٲ۴�.
	if (targetB->bState != EPlayerBState::B_Locking && currentTime > CheckTime)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);
		GoToRandomWaypoint();

		m_state = EEnemyState::Idle;
		currentTime = 0;
	}

	//���� �÷��̾� A�� ��ȭ ��û�� �Ѵٸ�
	if (me->inEnemyTriggerA == true && targetA->aState == EPlayerAState::Talk)
	{
		//A�� ��ȭ ��û�� �Ѵٸ� enemy�� Talk�� ���� ���ϴ� ���� �����
		m_state = EEnemyState::Talk;
	}
	//���� �÷��̾� B�� ��ȭ ��û�� �Ѵٸ�
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
	
	//���� UI ���
	//���� �ִϸ��̼� 
	
	UGameplayStatics::OpenLevel(this, "FailMap");

}


ATargetPoint* AEnemyAIController::GetRandomWaypoint()
{
//�����ϰ� ����Ʈ ����
	CALLINFO();
auto index = FMath::RandRange(2, Waypoints.Num()-1);
return Cast<ATargetPoint>(Waypoints[index]);
}

void AEnemyAIController::GoToRandomWaypoint()
{
	CALLINFO();
	//���� ����Ʈ �̵�
	MoveToActor(GetRandomWaypoint());
}

ATargetPoint* AEnemyAIController::WaypointA()
{
	//A�� ������ ��
	auto index = FMath::RandRange(0, 0);
	return Cast<ATargetPoint>(Waypoints[index]);

}

ATargetPoint* AEnemyAIController::WaypointB()
{
	//B�� ��������
	auto index = FMath::RandRange(1, 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

