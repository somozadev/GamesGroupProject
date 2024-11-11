// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AttackComponent.h"
#include "AIEnemy.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API AAIEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemy();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Behavior")
		class UBehaviorTree* m_behaviorTree;

protected:
	UPROPERTY(EditAnywhere, Category = "Behavior", Meta = (MakeEditWidget = true))
		FVector m_patrolPoint1;
	UPROPERTY(EditAnywhere, Category = "Behavior", Meta = (MakeEditWidget = true))
		FVector m_patrolPoint2;
	UPROPERTY(EditAnywhere, Category = "Behavior", Meta = (MakeEditWidget = true))
		FVector m_patrolPoint3;
	UPROPERTY(EditAnywhere, Category = "Behavior", Meta = (MakeEditWidget = true))
		FVector m_patrolPoint4;

	unsigned int m_nearestPatrolPoint = 1;
	bool m_isInChaseRange = false;
	FVector m_currentPatrolTarget;
	TArray<UAttackComponent*> m_attackComponents;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStats")
		int m_maxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyStats")
		float m_attackCooldown = 2.0f;

	class ABaseAIEnemyController* m_controller;
	AActor* m_playerCharacter;
	int m_currentHealth;
	bool m_isAlive = true;

	FTimerHandle m_timerHandle;
	FTimerDelegate m_timerDelegate;
	float m_timeSinceLastAttack = 0.0f;
	float m_multihitTimer = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_warningMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ConsiderAttack();

	void AttackA();
	void AttackB();
	void AttackC();
	void CalculateNearestPatrolPoint();
	UFUNCTION()
		void PerformDelayedAttack(int index);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		bool TakeAttackDamage(int damage);

	UFUNCTION(BlueprintCallable)
		bool GetIsAlive();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	friend class UBTTaskAttack;
};
