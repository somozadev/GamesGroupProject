
#include "BaseChest.h"
#include "EventsManager.h"

ABaseChest::ABaseChest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseChest::BeginPlay()
{
	Super::BeginPlay();
	FOnCustomEvent::FDelegate delegate;
	delegate.BindUFunction(this, FName("InteractInputTriggerToUse"));
	if (UEventsManager::Get())
	{
		UEventsManager::Get()->Subscribe(FName("InteractEvent"), delegate);
		UE_LOG(LogTemp, Warning, TEXT("Chest subscribed to InteractEvent"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EventsManager instance is null!"));
	}}

void ABaseChest::InteractInputTriggerToUse()
{
	if (!InContact)return;
	OnChestUsed.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Use done and chest interacted"));
}
