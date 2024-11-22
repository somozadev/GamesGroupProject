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
	UPROPERTY(VisibleAnywhere)
	TArray<FVector2D> InventoryActive; //={FVector2D::ZeroVector}
	UPROPERTY(VisibleAnywhere)
	int currentCurrency;
	UPROPERTY(VisibleAnywhere)
	float currentHp; 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION() //requires to have UFUNCTION() for the eventsmanager 
	void AddCard(int ID);
	UFUNCTION()
	bool UseCard(int ID);
	UFUNCTION() 
	void AddCurrency(int Amount);
	UFUNCTION()
	bool UseCurrency(int Amount);
	UFUNCTION()
	float LoadCurrentHp() const;
	UFUNCTION()
	void SaveCurrentHp(float HP);
	
};
