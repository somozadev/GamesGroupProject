// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <string>
#include "EventsList.generated.h"

/**
 * 
 */
UCLASS()
class GAMESGROUPPROJECT_API UEventsList : public UObject
{
	GENERATED_BODY()

public: 
	void OnCardPickedUp(FString card_id); 
	
};
