// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamesGroupProjectGameMode.h"
#include "GamesGroupProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGamesGroupProjectGameMode::AGamesGroupProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
