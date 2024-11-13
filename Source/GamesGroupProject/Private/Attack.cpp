// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack.h"

Attack::Attack()
{
}

Attack::~Attack()
{
}

bool Attack::PerformAttack_Implementation(AActor* target, AActor* instigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("I am the default C++ attack function. This was probably called by mistake")));
	return false;
}