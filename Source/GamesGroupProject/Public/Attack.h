// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAMESGROUPPROJECT_API Attack
{
public:
	Attack();
	~Attack();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	virtual bool PerformAttack(AActor* target, AActor* instigator) = 0;
	virtual bool PerformAttack_Implementation(AActor* target, AActor* instigator);
};
