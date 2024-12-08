// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUseInteractable.h"
#include "BaseChest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChestUsed);
UCLASS()
class GAMESGROUPPROJECT_API ABaseChest : public ABaseUseInteractable
{
	GENERATED_BODY()

public:
	ABaseChest();
	UFUNCTION()
	void InteractInputTriggerToUse();
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnChestUsed OnChestUsed;
protected:
	virtual void BeginPlay() override;
};
