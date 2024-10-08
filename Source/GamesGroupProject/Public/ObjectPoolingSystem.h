// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolingSystem.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API AObjectPoolingSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectPoolingSystem();

protected:
	UPROPERTY(EditAnywhere, Category = ObjectPoolSettings)
		TArray<TSubclassOf<AActor>> m_objects;

	UPROPERTY(EditAnywhere, Category = ObjectPoolSettings)
		TArray<int> m_numToSpawn;

	TArray<TArray<AActor*>> m_pool;
	TArray<int> m_nextToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		AActor* SpawnFromPool(int objectCode, FTransform spawnPoint);

	UFUNCTION(BlueprintCallable)
		void DisableAllObjectsInPool();
};
