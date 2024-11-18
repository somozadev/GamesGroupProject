#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "BaseCard.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API ABaseCard : public AInteractable
{
	GENERATED_BODY()
protected:
	virtual void HandlePickup(AActor* interactorActor) override;

public:
	UPROPERTY(EditAnywhere, Category="Cards")
	int ID;
	/* Based on cardHolds table 
		* 0 -> Combat Lava card 
		* 1 -> Combat Poision card 
		* 2 -> Combat Thunder card
		* 3 -> Puzzle Floating card
		* 4 -> Puzzle Laser card
		* 5 -> Puzzle Magnetism card
	*/
};
