#pragma once

#include "CoreMinimal.h"
#include "CardComponent.h"
#include "SpawnerCardComponent.generated.h"

class AObjectPoolingSystem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API USpawnerCardComponent : public UCardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawnerCardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	int m_attackObjectType;
	AObjectPoolingSystem* m_objectPool;
	UStaticMeshComponent* m_targetReticle;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ActivateCard() override;
	virtual bool UseCard() override;
	virtual bool UseCard(AActor* target) override;
	virtual bool UseCard(TArray<AAIEnemy*>& targets) override;
	virtual bool DeactivateCard() override;
};
