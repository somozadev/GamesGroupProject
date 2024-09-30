// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
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

	class ABaseAIEnemyController* m_controller;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
