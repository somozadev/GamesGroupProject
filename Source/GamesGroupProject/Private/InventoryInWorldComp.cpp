// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryInWorldComp.h"
#include "StructForInventoryDesc.h"


// Sets default values
AInventoryInWorldComp::AInventoryInWorldComp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AInventoryInWorldComp::BeginPlay()
{
	Super::BeginPlay();
	
	
	

	
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
	for (FtempCardBaseLine* NamedPoint:Outputingpoint )
	{
		int workingID = NamedPoint->ID;
		if (workingID == ID)
		{
			pickpoint = index;
		}
		index ++;
	}
	if (pickpoint != -1)
	{
		bool test=false;
		for (FVector2D pointer : InventoryActive)
		{
			if(pointer.X == ID)
			{
				pointer.Y=pointer.Y+1;
				test=true;
			}
		}
		InventoryActive.Add(FVector2D(ID,1));
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

