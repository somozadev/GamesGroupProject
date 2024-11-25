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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector2D> InventoryActive={FVector2D::ZeroVector}; 
	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	bool save();
	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	bool load(); 
	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	bool clear();
	//UPROPERTY(EditAnywhere)

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() //requires to has UFUNCTION() for the eventsmanager 
	void AddCard(int ID);
	bool UseCard(int ID);
	
};
