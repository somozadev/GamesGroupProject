// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUseInteractable.h"
#include "BaseKey.generated.h"

/**
 * 
 */
UCLASS()
class GAMESGROUPPROJECT_API ABaseKey : public ABaseUseInteractable
{
	GENERATED_BODY()

public:
	ABaseKey();
	UFUNCTION()
	void InteractInputTriggerToUse();

protected:
	virtual void BeginPlay() override;

};
