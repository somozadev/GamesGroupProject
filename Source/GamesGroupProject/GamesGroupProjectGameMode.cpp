// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamesGroupProjectGameMode.h"
//#include "PlayerCube.h"
#include "UObject/ConstructorHelpers.h"

AGamesGroupProjectGameMode::AGamesGroupProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GroupProject/Player/BP_NewPlayerCube"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
