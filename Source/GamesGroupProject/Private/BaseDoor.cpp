#include "BaseDoor.h"
#include "EventsManager.h"
#include "GameFramework/RotatingMovementComponent.h"


ABaseDoor::ABaseDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	if (RotationMovement)
	{
		RotationMovement->bRotationInLocalSpace = true;
		RotationMovement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	}
	IsOpen = false;
}

void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();
	FOnCustomEvent::FDelegate delegate;
	delegate.BindUFunction(this, FName("InteractInputTriggerToUse"));
	UEventsManager::Get()->Subscribe(FName("InteractEvent"), delegate);
	FOnCustomEvent::FDelegate unlockDoorDelegate;
	unlockDoorDelegate.BindUFunction(this, FName("UnlockDoor"));
	UEventsManager::Get()->Subscribe(FName("OnUseKeyAcquired"), unlockDoorDelegate);
}

void ABaseDoor::UnlockDoor()
{
	IsOpen = true;
}

void ABaseDoor::InteractInputTriggerToUse()
{
	if (!InContact) return;
	if (!IsOpen)return;
	// UEventsManager::Get()->Invoke(FName("DoorOpened"));
	WhenDoorOpened();
}

void ABaseDoor::WhenDoorOpened()
{
	UE_LOG(LogTemp, Warning, TEXT("The door has been opened!"));
	OnDoorOpened_BP();
}
