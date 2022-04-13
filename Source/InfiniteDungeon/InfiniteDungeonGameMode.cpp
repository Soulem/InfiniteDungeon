// Copyright Epic Games, Inc. All Rights Reserved.

#include "InfiniteDungeonGameMode.h"
#include "InfiniteDungeonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInfiniteDungeonGameMode::AInfiniteDungeonGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
