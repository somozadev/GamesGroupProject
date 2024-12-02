// Fill out your copyright notice in the Description page of Project Settings.


#include "InvincibilityCardComponent.h"

#include "PlayerCube.h"


// Sets default values for this component's properties
UInvincibilityCardComponent::UInvincibilityCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInvincibilityCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInvincibilityCardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UInvincibilityCardComponent::PrintToScreenIsSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("CARD INVINCIBLE ABILITY ")));
}

bool UInvincibilityCardComponent::UseCard()
{
	if (m_isInUse)
		return DeactivateCard();
	
	if (!Super::UseCard())
		return false;

	if (m_player != nullptr)
	{
		m_player->SetIsInvincible(true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("INVINCIBLE!")));
		return true;
	}

	return false;
}

bool UInvincibilityCardComponent::UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets)
{
	return UseCard();
}

bool UInvincibilityCardComponent::DeactivateCard()
{
	if (!Super::DeactivateCard())
		return false;

	if (m_player != nullptr)
	{
		m_player->SetIsInvincible(false);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Not Invincible!")));
		return true;
	}

	return false;
}

