// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryInWorldComp.h"

#include "EventsManager.h"
#include "StructForInventoryDesc.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// Sets default values
AInventoryInWorldComp::AInventoryInWorldComp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


bool AInventoryInWorldComp::save()
{
	bool success = true;

	//TSharedRef< FJsonObject > SaveFile = MakeShared<FJsonObject>();
	
	return success;
	
}

bool AInventoryInWorldComp::load()
{
	bool success = true;

	return success;
}

bool AInventoryInWorldComp::clear()
{
	bool success = true;
	return success;
}

// Called when the game starts or when spawned
void AInventoryInWorldComp::BeginPlay()
{
	Super::BeginPlay();
	
	FOnCustomEventOneParamInt::FDelegate delegate;
	delegate.BindUFunction(this, FName("AddCard"));
	UEventsManager::Get()->Subscribe(FName("OnCardPickedUp"), delegate);
	
	UE_LOG(LogTemp, Warning, TEXT("Inventory Activating"));
	
//	FString s = InvCardPossible;
	
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
    
	int pickpoint=-1;
	int index=0;
	UE_LOG(LogTemp, Warning, TEXT("AddCard invoked with ID: %d"), ID);
	for (FtempCardBaseLine* NamedPoint:Outputingpoint )
	{
		
		int workingID = NamedPoint->ID;
		
		if (workingID == ID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Succeed: %d %d"), ID , workingID);
			pickpoint = index;
		}
		index ++;
	}
	if (pickpoint != -1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Card: %d "), ID);
		bool test=false;
		for (FVector2D& pointer : InventoryActive)
		{
			int c =pointer.X;
			if(c == ID)
			{
				pointer.Y=pointer.Y+1;
				test=true;
			}
		}
		if (test==false)
		{
			InventoryActive.Add(FVector2D(ID,1));
		}
		return ;
	}
	else return;
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

