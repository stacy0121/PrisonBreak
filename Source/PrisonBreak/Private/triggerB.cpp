// Fill out your copyright notice in the Description page of Project Settings.


#include "triggerB.h"
#include <Components/BoxComponent.h>
#include "Enemy.h"
#include "PrisonBreak.h"

// Sets default values
AtriggerB::AtriggerB()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collision;

}

// Called when the game starts or when spawned
void AtriggerB::BeginPlay()
{
	Super::BeginPlay();
	
	collision->OnComponentBeginOverlap.AddDynamic(this, &AtriggerB::OnBeginOverlap);
	collision->OnComponentEndOverlap.AddDynamic(this, &AtriggerB::OnEndOverlap);

}

// Called every frame
void AtriggerB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AtriggerB::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{


	auto me = Cast<AEnemy>(OtherActor);

	if (me)
	{
		me->inEnemyTriggerB = true;
		CALLINFO();
	}

}

void AtriggerB::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	auto me = Cast<AEnemy>(OtherActor);

	if (me)
	{
		me->inEnemyTriggerB = false;
		CALLINFO();
	}

}

