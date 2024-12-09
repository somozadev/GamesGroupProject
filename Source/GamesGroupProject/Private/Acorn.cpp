#include "Acorn.h"
#include "EventsManager.h"

AAcorn::AAcorn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAcorn::HandlePickup(AActor* interactorActor)
{
	
	if (interactorActor)
	{
		UEventsManager::Get()->Invoke(FName("OnAcornPickedUp"), amount);
		Destroy();
	}
}
