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
	TArray<FVector2D> InventoryActive; //={FVector2D::ZeroVector}
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "MID LEVEL SAVE LOAD STUFF")
	int currentCurrency;
	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	int GetAcorns();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float currentHp; 

	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	bool save(TArray<FVector2D> replacement);
	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	TArray<FVector2D> load(); 
	UFUNCTION(BlueprintCallable, Category = "MID LEVEL SAVE LOAD STUFF")
	bool clear();
	//UPROPERTY(EditAnywhere)

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, Category ="inventoryBlueprint") //requires to have UFUNCTION() for the eventsmanager 
	void AddCard(int ID);
	UFUNCTION(BlueprintCallable, Category ="inventoryBlueprint")
	bool UseCard(int ID);
	UFUNCTION(BlueprintCallable, Category ="inventoryBlueprint") 
	void AddCurrency(int Amount);
	UFUNCTION(BlueprintCallable, Category ="inventoryBlueprint")
	bool UseCurrency(int Amount);
	UFUNCTION(BlueprintCallable, Category ="inventoryBlueprint")
	float LoadCurrentHp() const;
	UFUNCTION(BlueprintCallable, Category ="inventoryBlueprint")
	void SaveCurrentHp(float HP);
	
};
