// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolingSystem.h"

// Sets default values
AObjectPoolingSystem::AObjectPoolingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectPoolingSystem::BeginPlay()
{
	Super::BeginPlay();

	if (m_numToSpawn.Num() < m_objects.Num())
	{
		unsigned int numToAdd = m_objects.Num() - m_numToSpawn.Num();
		for (unsigned int i = 0; i < numToAdd; i++)
		{
			m_numToSpawn.Add(10);
		}
	}
	
	UWorld* world = GetWorld();

	for (size_t i = 0; i < m_objects.Num(); i++)
	{
		if (m_numToSpawn[i] <= 0)
			continue;

		TArray<AActor*> newPool;
		for (size_t j = 0; j < m_numToSpawn[i]; j++)
		{
			AActor* obj = world->SpawnActor(m_objects[i]);
			obj->SetActorHiddenInGame(true);
			obj->SetActorEnableCollision(false);
			obj->SetActorLocation(FVector(0.0f, 10000.0f, 5000.0f));
			obj->SetActorTickEnabled(false);
			newPool.Add(obj);
		}

		m_pool.Add(newPool);
		m_nextToSpawn.Add(0);
	}
}

// Called every frame
void AObjectPoolingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* AObjectPoolingSystem::SpawnFromPool(int objectCode, FTransform spawnPoint)
{
	if (objectCode >= m_objects.Num() || objectCode < 0)
		return nullptr;

	if (m_nextToSpawn[objectCode] >= m_pool[objectCode].Num())
		m_nextToSpawn[objectCode] = 0;

	AActor* selectedObject = nullptr;

	if (m_pool[objectCode][m_nextToSpawn[objectCode]])
	{
		selectedObject = m_pool[objectCode][m_nextToSpawn[objectCode]];
		selectedObject->SetActorHiddenInGame(false);
		selectedObject->SetActorEnableCollision(true);
		selectedObject->SetActorTickEnabled(true);
		selectedObject->SetActorTransform(spawnPoint);
		m_nextToSpawn[objectCode]++;
	}

	return selectedObject;
}

void AObjectPoolingSystem::DisableAllObjectsInPool()
{
	for (size_t i = 0; i < m_pool.Num(); i++)
	{
		for (size_t j = 0; j < m_pool[i].Num(); j++)
		{
			m_pool[i][j]->SetActorHiddenInGame(true);
			m_pool[i][j]->SetActorEnableCollision(false);
			m_pool[i][j]->SetActorLocation(FVector(0.0f, 10000.0f, 5000.0f));
			m_pool[i][j]->SetActorTickEnabled(false);
		}
	}
}

