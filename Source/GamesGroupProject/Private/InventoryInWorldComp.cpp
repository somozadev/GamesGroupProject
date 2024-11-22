// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryInWorldComp.h"

#include "EventsManager.h"
#include "StructForInventoryDesc.h"


AInventoryInWorldComp::AInventoryInWorldComp()
{
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AInventoryInWorldComp::BeginPlay()
{
	Super::BeginPlay();
	FOnCustomEventOneParamInt::FDelegate cardPickupDelegate;
	FOnCustomEventOneParamInt::FDelegate acornPickupDelegate;
	cardPickupDelegate.BindUFunction(this, FName("AddCard"));
	acornPickupDelegate.BindUFunction(this, FName("AddCurrency"));
	UEventsManager::Get()->Subscribe(FName("OnCardPickedUp"), cardPickupDelegate);
	UEventsManager::Get()->Subscribe(FName("OnAcornPickedUp"), acornPickupDelegate);
	
	
	
	FString a;
	InvCardPossible->GetAllRows(a, Outputingpoint);
	try
	{
		for (FtempCardBaseLine* NamedPoint:Outputingpoint )
		{
			FString s = NamedPoint->Name;    
			UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
		}
		FString inventoryroll;//=a:
		if(inventoryroll.Contains(TEXT("Test")))
		{
			UE_LOG(LogTemp, Warning, TEXT("Test card has worked"));
		}
	}
	catch (...)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Error"));
	}
	
}

// Called every frame
void AInventoryInWorldComp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventoryInWorldComp::AddCard(int ID)
{
	UE_LOG(LogTemp, Warning, TEXT("AddCard invoked with ID: %d"), ID);

	int pickpoint = -1;
	int index = 0;

	for (FtempCardBaseLine* NamedPoint : Outputingpoint)
	{
		int workingID = NamedPoint->ID;
		if (workingID == ID)
		{
			pickpoint = index;
		}
		index++;
	}
	if (pickpoint != -1)
	{
		bool found = false;

		for (FVector2D& pointer : InventoryActive) 
		{
			if (pointer.X == ID)
			{
				pointer.Y = pointer.Y + 1; 
				found = true;
				break; 
			}
		}
		if (!found)
			InventoryActive.Add(FVector2D(ID, 1));
	}
}

bool AInventoryInWorldComp::UseCard(int ID)
{
	int pickpoint=-1;
	int index=0;
	for (FtempCardBaseLine* NamedPoint:Outputingpoint )
	{
		int workingID = NamedPoint->ID;
		if (workingID == ID)
		{
			pickpoint = index;
		}
		index ++;
	}
	if (pickpoint == -1)
	return (false);
	else
	{
		bool test=false;
		for (FVector2D pointer : InventoryActive)
		{
			if(pointer.X == ID)
			{
				pointer.Y=pointer.Y-1;
				test=true;
				if (pointer.Y < 0) {
					test = false;
					pointer.Y = 0;
				}
			}
		}
		return (test);
	}
}


void AInventoryInWorldComp::AddCurrency(const int Amount)
{
	currentCurrency += Amount;
}
bool AInventoryInWorldComp::UseCurrency(const int Amount)
{
	if(currentCurrency - Amount >= 0 )
	{
		currentCurrency -= Amount;
		return true;
	}
	return false;
}
float AInventoryInWorldComp::LoadCurrentHp() const
{
	return currentHp;
}
void AInventoryInWorldComp::SaveCurrentHp(const float HP)
{
	currentHp = HP;
}

