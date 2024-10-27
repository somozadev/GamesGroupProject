// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent_GroundPound.h"

bool UAttackComponent_GroundPound::PerformAttack_Implementation(AActor* target, AActor* instigator)
{
	//TODO - Set attack timer on enemy. Have it effect a bool that effects the behaviour tree
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Ground Pound!")));
	return false;
}
