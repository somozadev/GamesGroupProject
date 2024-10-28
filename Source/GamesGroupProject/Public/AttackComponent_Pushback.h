// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "AttackComponent_Pushback.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,Blueprintable))
class GAMESGROUPPROJECT_API UAttackComponent_Pushback : public UAttackComponent
{
	GENERATED_BODY()

public:
	UAttackComponent_Pushback();
	
	bool PerformAttack_Implementation(AActor* target, AActor* instigator) override;
};
