// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerA_Door.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerA.h"

// Sets default values
APlayerA_Door::APlayerA_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = collision;

	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMesh->SetupAttachment(collision);
}

// Called when the game starts or when spawned
void APlayerA_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerA_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerA_Door::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APlayerA_Door::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

