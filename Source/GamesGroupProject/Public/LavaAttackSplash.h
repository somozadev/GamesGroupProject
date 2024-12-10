// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LavaAttackSplash.generated.h"
class AAIEnemy;

UCLASS()
class GAMESGROUPPROJECT_API ALavaAttackSplash : public AActor
{
	GENERATED_BODY()

public:
	ALavaAttackSplash();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<USphereComponent> DamageArea;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	double SplashDuration =4.5f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	double SplashTickDamageDuration = 2.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Default")
	bool EnemyInSplash;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Default")
	 TArray<AAIEnemy*> EnemiesInSplash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int32 Damage = 1.0f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	                    bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	double ElapsedSplashDuration;
	double ElapsedToTickDmgSplashDuration;
};
