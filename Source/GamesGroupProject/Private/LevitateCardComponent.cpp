// Fill out your copyright notice in the Description page of Project Settings.


#include "LevitateCardComponent.h"

#include "PlayerCube.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
ULevitateCardComponent::ULevitateCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevitateCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void ULevitateCardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_isInUse)
	{
		if (m_player)
		{
			const UCharacterMovementComponent* MovementComponent = m_player->GetCharacterMovement();
			if (MovementComponent && MovementComponent->IsFlying())
			{
				float InputValue = m_player->GetInputAxisValue("FloatUpDown");
				FVector UpwardVector = m_player->GetActorUpVector();
				m_player->AddMovementInput(UpwardVector, InputValue);
			}
		}
	}
	// ...
}

bool ULevitateCardComponent::UseCard()
{
	if (m_isInUse)
		return DeactivateCard();

	if (!Super::UseCard())
		return false;
	if (m_player)
	{
		m_player->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Levitation Activated!"));
		return true;
	}

	return false;
}

bool ULevitateCardComponent::UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets)
{
	return UseCard();
}

bool ULevitateCardComponent::DeactivateCard()
{
	if (!Super::DeactivateCard())
		return false;

	if (m_player)
	{
		m_player->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Levitation Deactivated!"));
		return true;
	}

	return false;
}
