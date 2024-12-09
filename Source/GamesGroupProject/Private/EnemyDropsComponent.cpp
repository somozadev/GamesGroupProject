#include "EnemyDropsComponent.h"
#include "EventsManager.h"

UEnemyDropsComponent::UEnemyDropsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// FOnCustomEvent eventDelegate = FOnCustomEvent();
	// eventDelegate.AddDynamic(this, &UEnemyDropsComponent::OnItemsDropped);
	// UEventsManager::Get()->EventMap.Add("OnItemsDropped", eventDelegate);
	minRandomSpawnRadius = 250.0f;
	maxRandomSpawnRadius = 550.0f;
}

void UEnemyDropsComponent::Drop()
{
	UE_LOG(LogTemp, Error, TEXT("DROPCALLED"));
	FDropItems DropItems;
	DropItems = GetProbabilityDrop(dropType, Level);
	SpawnItems(DropItems);
}

FDropItems UEnemyDropsComponent::GetProbabilityDrop(ECardDropType CardDropType, ELevel Level)
{
	FDropItems DropItems;
	float RandomChance = FMath::FRandRange(0.f, 100.f);
	float RandomCorn = FMath::RandRange(3, 6);
	switch (Level)
	{
	case ELevel::Level1:
		if (CardDropType == ECardDropType::Combat)
		{
			if (RandomChance <= 70.f)
				DropItems = FDropItems(2, 2, 0, 0, 0, 0, 0, 0, 0);
			else if (RandomChance <= 95.f)
				DropItems = FDropItems(1, 1, 1, 0, 0, 0, 0, 0, 0);
			else
				DropItems = FDropItems(1, 1, 0, 0, 1, 0, 0, 0, 0);
		}
		else if (CardDropType == ECardDropType::Chest)
			DropItems = FDropItems(RandomCorn, 0, 0, 0, 0, 0, 0, 0, 0);

	// else if (CardDropType == ECardDropType::Puzzle)
	// 	if (RandomChance <= 40.f)
	// 		DropItems = FDropItems(2, 0, 0, 0, 0, 0, 1, 0, 0);
	// 	else if (RandomChance <= 100.f)
	// 		DropItems = FDropItems(1, 0, 0, 0, 0, 0, 2, 0, 0);
		break;

	case ELevel::Level2:
		if (CardDropType == ECardDropType::Combat)
		{
			if (RandomChance <= 35.f)
				DropItems = FDropItems(1, 2, 1, 1, 0, 0, 0, 0, 0);
			else if (RandomChance <= 65.f)
				DropItems = FDropItems(0, 2, 1, 1, 0, 0, 0, 0, 0);
			else if (RandomChance <= 95.f)
				DropItems = FDropItems(2, 0, 0, 0, 1, 1, 0, 0, 0);
			else
				DropItems = FDropItems(1, 1, 0, 0, 1, 0, 0, 0, 0);
		}
		else if (CardDropType == ECardDropType::Chest)
			DropItems = FDropItems(RandomCorn, 0, 0, 0, 0, 0, 0, 0, 0);

	// else if (CardDropType == ECardDropType::Puzzle)
	// 	if (RandomChance <= 30.f)
	// 		DropItems = FDropItems(3, 0, 0, 0, 0, 0, 0, 2, 0);
	// 	else if (RandomChance <= 100.f)
	// 		DropItems = FDropItems(2, 0, 0, 0, 0, 0, 0, 1, 0);
		break;

	case ELevel::Level3:
		if (CardDropType == ECardDropType::Combat)
		{
			if (RandomChance <= 40.f)
				DropItems = FDropItems(2, 1, 1, 2, 0, 0, 0, 0, 0);
			else if (RandomChance <= 80.f)
				DropItems = FDropItems(1, 1, 2, 1, 0, 0, 0, 0, 0);
			else if (RandomChance <= 95.f)
				DropItems = FDropItems(3, 0, 1, 1, 0, 0, 0, 0, 0);
			else
				DropItems = FDropItems(1, 0, 0, 0, 1, 1, 0, 0, 0);
		}
		else if (CardDropType == ECardDropType::Chest)
			DropItems = FDropItems(RandomCorn, 0, 0, 0, 0, 0, 0, 0, 0);

	// else if (CardDropType == ECardDropType::Puzzle)
	// 	if (RandomChance <= 30.f)
	// 		DropItems = FDropItems(2, 0, 0, 0, 0, 0, 0, 0, 1);
	// 	else if (RandomChance <= 100.f)
	// 		DropItems = FDropItems(1, 0, 0, 0, 0, 0, 0, 0, 2);

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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("SPAWN DROP CALLED ")));

	if (Items.Acorns > 0)
	{
		for (int i = 0; i < Items.Acorns; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Acorn(s)"), Items.Acorns);
			if (acornBP)
				SpawnDroppedElement(acornBP);
		}
	}
	if (Items.Lava > 0)
	{
		for (int i = 0; i < Items.Lava; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Lava Combat Card(s)"), Items.Lava);
			if (lavaBP)
				SpawnDroppedElement(lavaBP);
		}
	}
	if (Items.Thunder > 0)
	{
		for (int i = 0; i < Items.Thunder; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Thunder Combat Card(s)"), Items.Thunder);
			if (thunderBP)
				SpawnDroppedElement(thunderBP);
		}
	}
	if (Items.Toxin > 0)
	{
		for (int i = 0; i < Items.Toxin; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Toxin Combat Card(s)"), Items.Toxin);
			if (toxinBP)
				SpawnDroppedElement(toxinBP);
		}
	}
	if (Items.Balance > 0)
	{
		for (int i = 0; i < Items.Balance; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Balance Combat Card(s)"), Items.Balance);
			if (balanceBP)
				SpawnDroppedElement(balanceBP);
		}
	}
	if (Items.Invincibility > 0)
	{
		for (int i = 0; i < Items.Invincibility; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Invincibility);
			if (invincibilityBP)
				SpawnDroppedElement(invincibilityBP);
		}
	}
	if (Items.Floating > 0)
	{
		for (int i = 0; i < Items.Floating; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Floating);
			if (floatingBP)
				SpawnDroppedElement(floatingBP);
		}
	}
	if (Items.Magnetism > 0)
	{
		for (int i = 0; i < Items.Magnetism; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Magnetism);
			if (magnetismBP)
				SpawnDroppedElement(magnetismBP);
		}
	}
	if (Items.Laser > 0)
	{
		for (int i = 0; i < Items.Laser; ++i)
		{
			UE_LOG(LogTemp, Warning, TEXT("Spawning %d Invincibility Card(s)"), Items.Laser);
			if (laserBP)
				SpawnDroppedElement(laserBP);
		}
	}
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

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AInteractable* item = GetWorld()->SpawnActor<AInteractable>(spawnable, spawnLocation, randomRotation,
		                                                            SpawnParams);
		if (item)
		{
			UStaticMeshComponent* meshComponent = item->FindComponentByClass<UStaticMeshComponent>();
			if (meshComponent && meshComponent->IsSimulatingPhysics())
			{
				FVector launchDirection = FVector(
					FMath::RandRange(-0.5f, 0.5f),
					FMath::RandRange(-0.5f, 0.5f),
					1.0f
				).GetSafeNormal();

				float launchStrength = FMath::RandRange(300.0f, 600.0f);
				meshComponent->AddImpulse(launchDirection * launchStrength, NAME_None, true);
			}
		}
	}
}

// Called when the game starts
void UEnemyDropsComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UEnemyDropsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
