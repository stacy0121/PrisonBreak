// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//더글라스 스켈레톤
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Enemy_BODY(TEXT("SkeletalMesh'/Game/Character/Enemy/Douglas__1_.Douglas__1_'"));
	if (Enemy_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Enemy_BODY.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -100));
	}

	//Mesh에 Animation 할당
	ConstructorHelpers::FClassFinder<UEnemyAnimInstance> tempAnim(TEXT("AnimBlueprint'/Game/Blueprint/BP_EAnimBlueprint.BP_EAnimBlueprint_C'"));

	if(tempAnim.Succeeded())
	{
	
	GetMesh()->SetAnimClass(tempAnim.Class);
	}

	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	//enemy ai 설정
//EnemyAIController가 스폰되면 자동으로 possess
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

