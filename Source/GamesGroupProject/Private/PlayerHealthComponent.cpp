// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthComponent.h"

#include "PlayerCube.h"

// Sets default values for this component's properties
UPlayerHealthComponent::UPlayerHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultBaseHealth = 100;
	Health = DefaultBaseHealth;
}


// Called when the game starts
void UPlayerHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if(Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UPlayerHealthComponent::TakeDamage);
	}
	
}

void UPlayerHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	APlayerCube* Owner = Cast<APlayerCube>(GetOwner());
	if(Owner)
	{
		if (Owner->GetIsInvincible())
			return;
	}
	
	if(Damage <= 0)
	{
		return;
	}
	else
		Health = FMath::Clamp(Health - Damage, 0.0f, DefaultBaseHealth);

	
	
}


