// Fill out your copyright notice in the Description page of Project Settings.


#include "CardComponent.h"

#include <Kismet/GameplayStatics.h>

#include "PlayerCube.h"

// Sets default values for this component's properties
UCardComponent::UCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	m_player = Cast<APlayerCube>(GetOwner());
	m_targetIndex = -1;
}


// Called when the game starts
void UCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UCardComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCardComponent::PrintToScreenIsSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("CARD XXX ")));

}

bool UCardComponent::ActivateCard()
{
	if (m_count <= 0)
		return false;

	return true;
}

bool UCardComponent::UseCard()
{
	if (!m_isReusable)
	{
		m_count--;
	}
	return true;
}

bool UCardComponent::UseCard(AActor* target)
{
	if (target == nullptr || !IsValid(target))
		return false;
	
	if (!m_isReusable)
	{
		m_count--;
	}
	return true;
}

bool UCardComponent::UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets)
{
	if (!m_isReusable)
	{
		m_count--;
	}
	return true;
}

bool UCardComponent::DeactivateCard()
{
	return true;
}

