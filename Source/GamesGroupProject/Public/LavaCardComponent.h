// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnerCardComponent.h"
#include "LavaCardComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API ULavaCardComponent : public USpawnerCardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULavaCardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PrintToScreenIsSelected() override;
	bool ActivateCard() override;
	bool UseCard(AActor* target) override;
	bool UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets) override;

};
