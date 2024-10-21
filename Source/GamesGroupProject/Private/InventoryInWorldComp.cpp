// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryInWorldComp.h"


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
	
	///for ()
	//{
	//	FString s = NamedPoint.ToString();
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
	//}
}

// Called every frame
void AInventoryInWorldComp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

