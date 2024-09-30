// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolingSystem.h"

// Sets default values
AObjectPoolingSystem::AObjectPoolingSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pool = TArray<TQueue<AActor*>>();

}

// Called when the game starts or when spawned
void AObjectPoolingSystem::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* world = GetWorld();

	for (size_t i = 0; i < m_objects.Num(); i++)
	{
		TQueue<AActor*> newPool = TQueue<AActor*>();
		size_t jMax = (m_numToSpawn.IsValidIndex(i) ? m_numToSpawn[i] : 10);
		for (size_t j = 0; j < jMax; j++)
		{
			AActor* obj = world->SpawnActor(m_objects[i]);
			obj->SetActorHiddenInGame(true);
			obj->SetActorEnableCollision(false);
			obj->SetActorLocation(FVector(0.0f, 10000.0f, 5000.0f));
			obj->SetActorTickEnabled(false);
			newPool.Enqueue(obj);
		}

		m_pool.Add(newPool);
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

	AActor* selectedObject = nullptr;

	if (m_pool[objectCode].Dequeue(selectedObject) && selectedObject)
	{
		selectedObject->SetActorHiddenInGame(false);
		selectedObject->SetActorEnableCollision(true);
		selectedObject->SetActorTickEnabled(true);
		selectedObject->SetActorTransform(spawnPoint);
		m_pool[objectCode].Enqueue(selectedObject);
	}

	return selectedObject;
}

void AObjectPoolingSystem::DisableAllObjectsInPool()
{
	for (size_t i = 0; i < m_pool.Num(); i++)
	{
		AActor* obj = nullptr;

		while (m_pool[i].Dequeue(obj))
		{
			obj->SetActorHiddenInGame(true);
			obj->SetActorEnableCollision(false);
			obj->SetActorLocation(FVector(0.0f, 10000.0f, 5000.0f));
			obj->SetActorTickEnabled(false);

			m_pool[i].Enqueue(obj);
		}
	}
}

