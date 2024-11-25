


#include "LightningCardComponent.h"

#include "AIEnemy.h"


// Sets default values for this component's properties
ULightningCardComponent::ULightningCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightningCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULightningCardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULightningCardComponent::ActivateCard()
{
	return Super::ActivateCard();
}

bool ULightningCardComponent::UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets)
{
	if (!Super::UseCard(target, otherTargets))
		return false;

	//Deal damage to all targets
	//Spawn the effect for the lightning

	if (otherTargets.Num() == 0)
		return false;
	
	AAIEnemy* enemy = Cast<AAIEnemy>(target);

	if (!enemy)
		return false;

	if (otherTargets.Num() == 1)
	{
		enemy->TakeAttackDamage(m_damage);
	}
	else
	{
		//Do multi attack stuff here
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("ZAP!")));
	return true;
}

