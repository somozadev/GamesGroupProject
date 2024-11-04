// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class GAMESGROUPPROJECT_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_damage = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_knockbackPower = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_knockbackHeight = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		bool m_isDelayedAttack = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_attackDelay = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		float m_attackRadius = 100.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool PerformAttack(AActor* target, AActor* instigator);
	
	virtual bool PerformAttack_Implementation(AActor* target, AActor* instigator);

	bool GetIsDelayed();
	float GetDelayTime();
	float GetAttackRadius();
};
