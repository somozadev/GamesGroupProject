// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUseInteractable.h"
#include "BaseNutShack.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShopOpened);
UCLASS()
class GAMESGROUPPROJECT_API ABaseNutShack : public ABaseUseInteractable
{
	GENERATED_BODY()
	
public:
	ABaseNutShack();
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnShopOpened OnShopOpened;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void InteractInputTriggerToUse();
};