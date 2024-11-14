// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "AttackComponent_GroundPound.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,Blueprintable))
class GAMESGROUPPROJECT_API UAttackComponent_GroundPound : public UAttackComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_slamRadius = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_slamDelay = 1.0f;
public:
	bool PerformAttack_Implementation(AActor* target, AActor* instigator) override;
};
