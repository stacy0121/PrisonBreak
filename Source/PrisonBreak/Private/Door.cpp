// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerA.h"
#include "PrisonBreak.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collision;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMesh->SetupAttachment(collision);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
	collision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnBeginOverlap);
	collision->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnEndOverlap);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto player = Cast<APlayerA>(OtherActor);

	if (player)
	{
		player->isInTrigger = true;
	}
}

void ADoor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto player = Cast<APlayerA>(OtherComp);

	if (player)
	{
		player->isInTrigger = false;
	}
}

void ADoor::DoorOpen()
{
	Destroy();
	CALLINFO();
}

