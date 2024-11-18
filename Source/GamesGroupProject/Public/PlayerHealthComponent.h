// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESGROUPPROJECT_API UPlayerHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Health")
	float DefaultBaseHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Health")	
	float Health;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
		
};
