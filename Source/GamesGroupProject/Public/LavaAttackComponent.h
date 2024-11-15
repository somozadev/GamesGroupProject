// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCube.h"
#include "LavaAttackComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API ULavaAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULavaAttackComponent();

protected:
	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UPROPERTY(VisibleAnywhere, Category = "Aiming")
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, Category = "Aiming")
	FVector TargetLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	TSubclassOf<AActor> TargetActorClass;

	UPROPERTY()
	AActor* TargetObject;
	
	UPROPERTY(VisibleAnywhere)
	APlayerCube* PlayerCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aiming")
	float AimRadius;

public:
	void StartAiming();
	void StopAiming();
	void UpdateTargetLocation(const FVector& NewLocation) const;
	void CreateTargetObject();
	void MoveTargetObject(const FVector& Direction) const;
};
