// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	ComponentTags.Add(FName("AttackComp"));
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UAttackComponent::PerformAttack_Implementation(AActor* target, AActor* instigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("I am the default C++ attack function. This was probably called by mistake")));
	return false;
}

bool UAttackComponent::GetIsDelayed()
{
	return m_isDelayedAttack;
}

float UAttackComponent::GetDelayTime()
{
	return m_attackDelay;
}

float UAttackComponent::GetAttackRadius()
{
	return m_attackRadius;
}

