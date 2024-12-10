// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/SphereComponent.h>

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CardComponent.generated.h"

class APlayerCube;
class AAIEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESGROUPPROJECT_API UCardComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int m_count;
	APlayerCube* m_player;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CardGenericData")
		bool m_isReusable = false;

	AActor* m_target;
	int m_targetIndex;

	AActor* SplashSpawnedObject;
	UPROPERTY(EditDefaultsOnly, Category = "Card")
	TSubclassOf<AActor> SplashObject;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PrintToScreenIsSelected();
	virtual bool ActivateCard();
	virtual bool UseCard();
	virtual bool UseCard(AActor* target);
	virtual bool UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets);
	virtual bool DeactivateCard();
};
