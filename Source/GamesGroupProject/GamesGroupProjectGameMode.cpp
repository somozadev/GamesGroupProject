// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamesGroupProjectGameMode.h"
//#include "PlayerCube.h"
#include "UObject/ConstructorHelpers.h"

AGamesGroupProjectGameMode::AGamesGroupProjectGameMode()
{
	// set default pawn class to our Blueprinted character
<<<<<<< HEAD
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/GroupProject/Player/BP_NewPlayerCube"));
=======
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
>>>>>>> main
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
