// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructForInventoryDesc.h"
#include "InventoryInWorldComp.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API AInventoryInWorldComp : public AActor
{
	GENERATED_BODY()
	TArray <FtempCardBaseLine*> Outputingpoint;
public:	
	// Sets default values for this actor's properties
	AInventoryInWorldComp();
	UPROPERTY(EditAnywhere)
	UDataTable* InvCardPossible;
	TArray<FVector2D> InventoryActive={FVector2D::ZeroVector};

	//UPROPERTY(EditAnywhere)

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddCard(int ID);
	bool UseCard(int ID);
	
};
