#pragma once

#include "CoreMinimal.h"
#include "CardComponent.h"
#include "StateCardComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API UStateCardComponent : public UCardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateCardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CardGenericData")
		float m_duration;

	float m_timeElapsed;
	bool m_isInUse = false;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool ActivateCard() override;
	virtual bool UseCard() override;
	virtual bool DeactivateCard() override;
};
