// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDropsComponent.h"

#include "EventsManager.h"

UEnemyDropsComponent::UEnemyDropsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	FOnCustomEvent eventDelegate = FOnCustomEvent();
	eventDelegate.AddDynamic(this, &UEnemyDropsComponent::OnItemsDropped);
	UEventsManager::Get()->EventMap.Add("OnItemsDropped", eventDelegate);
}

void UEnemyDropsComponent::Drop()
{
	FDropItems DropItems;
	DropItems = GetProbabilityDrop(dropType, Level);
	SpawnItems(DropItems);
}

FDropItems UEnemyDropsComponent::GetProbabilityDrop(ECardDropType CardDropType, ELevel Level)
{
	FDropItems DropItems;
	float RandomChance = FMath::FRandRange(0.f, 100.f);
	switch (Level)
	{
	case ELevel::Level1:
		if (CardDropType == ECardDropType::Combat)
			if (RandomChance <= 70.f)
				DropItems = FDropItems(2, 2, 0, 0, 0, 0, 0, 0, 0);
			else if (RandomChance <= 95.f)
				DropItems = FDropItems(1, 1, 1, 0, 0, 0, 0, 0, 0);
			else
				DropItems = FDropItems(1, 1, 0, 0, 1, 0, 0, 0, 0);
		else if (CardDropType == ECardDropType::Puzzle)
			if (RandomChance <= 40.f)
				DropItems = FDropItems(2, 0, 0, 0, 0, 0, 1, 0, 0);
			else if (RandomChance <= 100.f)
				DropItems = FDropItems(1, 0, 0, 0, 0, 0, 2, 0, 0);
		break;

	case ELevel::Level2:
		if (CardDropType == ECardDropType::Combat)
			if (RandomChance <= 35.f)
				DropItems = FDropItems(1, 2, 1, 1, 0, 0, 0, 0, 0);
			else if (RandomChance <= 65.f)
				DropItems = FDropItems(0, 2, 1, 1, 0, 0, 0, 0, 0);
			else if (RandomChance <= 95.f)
				DropItems = FDropItems(2, 0, 0, 0, 1, 1, 0, 0, 0);
			else
				DropItems = FDropItems(1, 1, 0, 0, 1, 0, 0, 0, 0);
		else if (CardDropType == ECardDropType::Puzzle)
			if (RandomChance <= 30.f)
				DropItems = FDropItems(3, 0, 0, 0, 0, 0, 0, 2, 0);
			else if (RandomChance <= 100.f)
				DropItems = FDropItems(2, 0, 0, 0, 0, 0, 0, 1, 0);
		break;

	case ELevel::Level3:
		if (CardDropType == ECardDropType::Combat)
			if (RandomChance <= 40.f)
				DropItems = FDropItems(2, 1, 1, 2, 0, 0, 0, 0, 0);
			else if (RandomChance <= 80.f)
				DropItems = FDropItems(1, 1, 2, 1, 0, 0, 0, 0, 0);
			else if (RandomChance <= 95.f)
				DropItems = FDropItems(3, 0, 1, 1, 0, 0, 0, 0, 0);
			else
				DropItems = FDropItems(1, 0, 0, 0, 1, 1, 0, 0, 0);
		else if (CardDropType == ECardDropType::Puzzle)
			if (RandomChance <= 30.f)
				DropItems = FDropItems(2, 0, 0, 0, 0, 0, 0, 0, 1);
			else if (RandomChance <= 100.f)
				DropItems = FDropItems(1, 0, 0, 0, 0, 0, 0, 0, 2);

		break;
	}
	return DropItems;
}

void UEnemyDropsComponent::OnItemsDropped()
{
	FString DropTypeString = UEnum::GetValueAsString(dropType);
	FString LevelString = UEnum::GetValueAsString(Level);
	FString GroupString = UEnum::GetValueAsString(Group);
	UE_LOG(LogTemp, Warning, TEXT("Items dropped of current cardType: %s, Level: %s and Group: %s"), *DropTypeString,
	       *LevelString, *GroupString);
}


void UEnemyDropsComponent::SpawnItems(const FDropItems& Items)
{
	if (Items.Acorns > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Acorn(s)"), Items.Acorns);
		// Add actual spawning logic here, e.g.:
		// GetWorld()->SpawnActor<AAcorn>(AcornClass, Location, Rotation);
	}
	if (Items.Lava > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Lava Combat Card(s)"), Items.Lava);
		// Add actual spawning logic here
	}
	if (Items.Thunder > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Thunder Combat Card(s)"), Items.Thunder);
		// Add actual spawning logic here
	}
	if (Items.Toxin > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Toxin Combat Card(s)"), Items.Toxin);
		// Add actual spawning logic here
	}
	if (Items.Balance > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Balance Combat Card(s)"), Items.Balance);
		// Add actual spawning logic here
	}
	if (Items.Invincibility > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Invincibility);
		// Add actual spawning logic here
	}
	
	UEventsManager::Get()->Invoke("OnItemsDropped");
}

// Called when the game starts
void UEnemyDropsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UEnemyDropsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
