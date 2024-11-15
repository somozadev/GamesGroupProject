// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "PlayerCube.h"
#include  "AIEnemy.h"
#include "AttackComponent_MultiHit.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GAMESGROUPPROJECT_API UAttackComponent_MultiHit : public UAttackComponent
{
	GENERATED_BODY()

protected:
	bool m_isAttacking = false;
	float m_currentAttackTime = 0.0f;
	int m_attackPhase = 0;
	APlayerCube* m_player;
	AAIEnemy* m_enemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		TArray<float> m_multiAttackTimings;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		TArray<float> m_multiAttackRadius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		TArray<float> m_multiAttackKnockbackPower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		TArray<float> m_multiAttackKnockbackHeight;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AttackData")
		TArray<int> m_multiAttackDamage;
public:
	bool PerformAttack_Implementation(AActor* target, AActor* instigator) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetCombinedDelayTimes();
	float GetCurrentRadius();
};
