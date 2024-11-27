// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseKey.h"
#include "EventsManager.h"

ABaseKey::ABaseKey()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseKey::BeginPlay()
{
	Super::BeginPlay();
	FOnCustomEvent::FDelegate delegate;
	delegate.BindUFunction(this, FName("InteractInputTriggerToUse"));
	if (UEventsManager::Get())
	{
		UEventsManager::Get()->Subscribe(FName("InteractEvent"), delegate);
		UE_LOG(LogTemp, Warning, TEXT("ABaseKey subscribed to InteractEvent"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EventsManager instance is null!"));
	}}

void ABaseKey::InteractInputTriggerToUse()
{
	if (!InContact)return;
	UEventsManager::Get()->Invoke(FName("OnUseKeyAcquired"));
	UE_LOG(LogTemp, Warning, TEXT("Use done and element picked up OnUseKeyAdquired!"));

	Destroy();
}

