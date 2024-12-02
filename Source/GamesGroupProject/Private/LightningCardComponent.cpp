


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

void ULightningCardComponent::PrintToScreenIsSelected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("CARD LIGHTNING ATTACK ")));
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
	else if (otherTargets.Num() == 2 || otherTargets.Num() == 3)
	{
		for (int i = 0; i < otherTargets.Num(); i++)
		{
			if (IsValid(otherTargets[i]))
			{
				otherTargets[i]->TakeAttackDamage(m_damage);
			}
		}
	}
	else
	{
		enemy->TakeAttackDamage(m_damage);

		FVector firstEnemyPos = enemy->GetActorLocation();
		float nearestDistOne = 9999999999999.0f;
		float nearestDistTwo = 9999999999999.0f;
		int nearestIndexOne = -1;
		int nearestIndexTwo = -1;

		for (int i = 0; i < otherTargets.Num(); i++)
		{
			if (!IsValid(otherTargets[i]))
				continue;

			if (otherTargets[i]->GetUniqueID() == enemy->GetUniqueID())
				continue;

			if (nearestIndexOne == -1)
			{
				nearestIndexOne = i;
				nearestDistOne = FVector::Dist(enemy->GetActorLocation(), otherTargets[i]->GetActorLocation());
			}
			else if (nearestIndexTwo == -1)
			{
				nearestIndexTwo = i;
				nearestDistTwo = FVector::Dist(enemy->GetActorLocation(), otherTargets[i]->GetActorLocation());
			}
			else
			{
				float currentDist = FVector::Dist(enemy->GetActorLocation(), otherTargets[i]->GetActorLocation());
				if (nearestDistOne > nearestDistTwo && currentDist < nearestDistOne)
				{
					nearestDistOne = currentDist;
					nearestIndexOne = i;
				}
				else if (nearestDistTwo >= nearestDistOne && currentDist < nearestDistTwo)
				{
					nearestDistTwo = currentDist;
					nearestIndexTwo = i;
				}
			}
		}

		if (nearestIndexOne != -1 && nearestIndexOne < otherTargets.Num())
		{
			otherTargets[nearestIndexOne]->TakeAttackDamage(m_damage);
		}

		if (nearestIndexTwo != -1 && nearestIndexTwo < otherTargets.Num())
		{
			otherTargets[nearestIndexTwo]->TakeAttackDamage(m_damage);
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("ZAP!")));
	return true;
}

