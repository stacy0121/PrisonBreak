// Fill out your copyright notice in the Description page of Project Settings.


#include "triggerA.h"
#include "PrisonBreak.h"
#include <Components/BoxComponent.h>
#include "Enemy.h"

// Sets default values
AtriggerA::AtriggerA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collision;

}

// Called when the game starts or when spawned
void AtriggerA::BeginPlay()
{
	Super::BeginPlay();

	collision->OnComponentBeginOverlap.AddDynamic(this, &AtriggerA::OnBeginOverlap);
	collision->OnComponentEndOverlap.AddDynamic(this, &AtriggerA::OnEndOverlap);
	
}

// Called every frame
void AtriggerA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AtriggerA::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	auto me = Cast<AEnemy>(OtherActor);

	if (me)
	{
		me->inEnemyTriggerA = true;
		CALLINFO();
	}
}

void AtriggerA::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	auto me = Cast<AEnemy>(OtherActor);

	if (me)
	{
		me->inEnemyTriggerA = false;
		CALLINFO();
	}

}

