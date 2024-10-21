// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryInWorldComp.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API AInventoryInWorldComp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryInWorldComp();
	UDataTable* InvCardPossible=LoadObject<UDataTable>(GetWorld(), TEXT("/Game/GroupProject/Inventory/AvalibleCards.AvalibleCards"));
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
