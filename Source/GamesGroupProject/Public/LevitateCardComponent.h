// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateCardComponent.h"
#include "LevitateCardComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API ULevitateCardComponent : public UStateCardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULevitateCardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PrintToScreenIsSelected() override;

	bool UseCard() override;
	bool UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets) override;
	bool DeactivateCard() override;

private:
	void ToggleMovementMode();
};
