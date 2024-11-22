


#include "StateCardComponent.h"


// Sets default values for this component's properties
UStateCardComponent::UStateCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStateCardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!m_isInUse)
		return;

	m_timeElapsed += DeltaTime;

	if (m_timeElapsed >= m_duration)
	{
		DeactivateCard();
	}
}

bool UStateCardComponent::ActivateCard()
{
	if (Super::ActivateCard())
		return false;
	
	return true;
}

bool UStateCardComponent::UseCard()
{
	Super::UseCard();

	m_timeElapsed = 0.0f;
	m_isInUse = true;
	//Calling player to toggle the state will happen in children
	return true;
}

bool UStateCardComponent::UseCard(AActor* target)
{
	return Super::UseCard(target);
}

bool UStateCardComponent::DeactivateCard()
{
	Super::DeactivateCard();
	m_isInUse = false;
	//Calling player to toggle the state will happen in children
	return true;
}

