#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Acorn.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API AAcorn : public AInteractable
{
	GENERATED_BODY()

public:
	AAcorn();

protected:
protected:
	virtual void HandlePickup(AActor* interactorActor) override;


public:
	UPROPERTY(EditAnywhere, Category="Acorn")
	int ID;
	UPROPERTY(EditAnywhere, Category="Acorn")
	int amount;
};
