// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNutShack.h"

#include "EventsManager.h"

ABaseNutShack::ABaseNutShack()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseNutShack::BeginPlay()
{
	Super::BeginPlay();
	FOnCustomEvent::FDelegate delegate;
	delegate.BindUFunction(this, FName("InteractInputTriggerToUse"));
	if (UEventsManager::Get())
	{
		UEventsManager::Get()->Subscribe(FName("InteractEvent"), delegate);
		UE_LOG(LogTemp, Warning, TEXT("Nutshack subscribed to InteractEvent"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EventsManager instance is null!"));
	}
}

void ABaseNutShack::InteractInputTriggerToUse()
{
	if (!InContact)return;
	OnShopOpened.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Use done and Shop interacted"));
}
