// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrisonBreakGameMode.h"
#include "PrisonBreakCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerB.h"

APrisonBreakGameMode::APrisonBreakGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	auto playerB = Cast<APlayerB>(GetOwner());
	UGameplayStatics::CreatePlayer(playerB, -1, true);
}
