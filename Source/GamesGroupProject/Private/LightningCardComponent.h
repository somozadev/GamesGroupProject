#pragma once

#include "CoreMinimal.h"
#include "SpawnerCardComponent.h"
#include "LightningCardComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API ULightningCardComponent : public USpawnerCardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULightningCardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* SecondSpawnedSplash;
	AActor* ThirdSpawnedSplash;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PrintToScreenIsSelected() override;
	bool ActivateCard() override;
	bool UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets) override;
};
