#include "BaseCard.h"
#include "EventsManager.h"

void ABaseCard::HandlePickup(AActor* interactorActor)
{
	if (interactorActor)
	{
		UEventsManager::Get()->Invoke(FName("OnCardPickedUp"), ID);
		Destroy();
	}
}
