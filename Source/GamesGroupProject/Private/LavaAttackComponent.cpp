// Fill out your copyright notice in the Description page of Project Settings.

#include "LavaAttackComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayerCube.h"
#include "Engine/World.h"


ULavaAttackComponent::ULavaAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsAiming = false;
	TargetLocation = FVector::ZeroVector;
}

void ULavaAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCube = Cast<APlayerCube>(GetOwner());
}

void ULavaAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void ULavaAttackComponent::StartAiming()
{
	bIsAiming = true;
	CreateTargetObject();
}

void ULavaAttackComponent::StopAiming()
{
	bIsAiming = false;
	if (TargetObject)
	{
		TargetObject->Destroy();
		TargetObject = nullptr;
	}
}
void ULavaAttackComponent::CreateTargetObject()
{
	if (PlayerCube && TargetActorClass)
	{
		const FVector SpawnLocation = PlayerCube->GetActorLocation() + FVector(0, AimRadius, 0);
		const FActorSpawnParameters SpawnParams;
		TargetObject = PlayerCube->GetWorld()->SpawnActor<AActor>(TargetActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}
void ULavaAttackComponent::UpdateTargetLocation(const FVector& NewLocation) const
{
	if (TargetObject)
		TargetObject->SetActorLocation(NewLocation);
}

void ULavaAttackComponent::MoveTargetObject(const FVector& Direction) const
{
	if (TargetObject)
	{
		FVector NewLocation = TargetObject->GetActorLocation() + Direction;
		UpdateTargetLocation(NewLocation);
	}
}
