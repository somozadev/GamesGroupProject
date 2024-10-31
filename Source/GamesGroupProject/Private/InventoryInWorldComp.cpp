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
	TArray <FtempCardBaseLine*> Outputingpoint;
	FString a;
	InvCardPossible->GetAllRows(a, Outputingpoint);
	try
	{
		for (FtempCardBaseLine* NamedPoint:Outputingpoint )
		{
			FString s = NamedPoint->Name;    
			UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
		}
		//FString inventoryroll;//=a:
		//if(inventoryroll.Contains(TEXT("Test")))
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("Test card has worked"));
		//}
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

