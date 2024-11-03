

#include "EnemyDropsComponent.h"
#include "EventsManager.h"

UEnemyDropsComponent::UEnemyDropsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	FOnCustomEvent eventDelegate = FOnCustomEvent();
	eventDelegate.AddDynamic(this, &UEnemyDropsComponent::OnItemsDropped);
	UEventsManager::Get()->EventMap.Add("OnItemsDropped", eventDelegate);
	minRandomSpawnRadius = 250.0f;
	maxRandomSpawnRadius = 550.0f;
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
		SpawnDroppedElement(acornBP);
	}
	if (Items.Lava > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Lava Combat Card(s)"), Items.Lava);
		// Add actual spawning logic here
		SpawnDroppedElement(lavaBP);

	}
	if (Items.Thunder > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Thunder Combat Card(s)"), Items.Thunder);
		// Add actual spawning logic here
		SpawnDroppedElement(thunderBP);
	}
	if (Items.Toxin > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Toxin Combat Card(s)"), Items.Toxin);
		// Add actual spawning logic here		
		SpawnDroppedElement(toxinBP);

	}
	if (Items.Balance > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Balance Combat Card(s)"), Items.Balance);
		// Add actual spawning logic here
		SpawnDroppedElement(balanceBP);
	}
	if (Items.Invincibility > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Invincibility);
		// Add actual spawning logic here  
		SpawnDroppedElement(invincibilityBP);
	}
	if (Items.Floating > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Floating);
		// Add actual spawning logic here  
		SpawnDroppedElement(floatingBP);
	}
	if (Items.Magnetism > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Magnetism);
		// Add actual spawning logic here  
		SpawnDroppedElement(magnetismBP);
	}
	if (Items.Laser > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Laser);
		// Add actual spawning logic here  
		SpawnDroppedElement(laserBP);
	}

	UEventsManager::Get()->Invoke("OnItemsDropped");
}

void UEnemyDropsComponent::SpawnDroppedElement(TSubclassOf<AInteractable> spawnable)
{
	if (GetWorld() && spawnable)
	{
		FVector ownerLocation = GetOwner()->GetActorLocation();
		float randomX = FMath::RandRange(minRandomSpawnRadius, maxRandomSpawnRadius) * (FMath::RandBool() ? 1 : -1); 
		float randomY = FMath::RandRange(minRandomSpawnRadius, maxRandomSpawnRadius) * (FMath::RandBool() ? 1 : -1); 
		FVector randomOffset = FVector(randomX, randomY, 0.0f);
		FVector spawnLocation = ownerLocation + randomOffset;


		FRotator randomRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);

		AInteractable* item = GetWorld()->SpawnActor<AInteractable>(spawnable, spawnLocation, randomRotation);
	}

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