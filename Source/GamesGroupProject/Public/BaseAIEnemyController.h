// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GAMESGROUPPROJECT_API ABaseAIEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseAIEnemyController();
	virtual void OnPossess(APawn* InPawn) override;
	UBlackboardComponent* GetBlackboard();
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Behavior")
		class UBlackboardComponent* m_blackboard;

	UPROPERTY(BlueprintReadWrite, Category = "Behavior")
		class UBehaviorTreeComponent* m_behaviorTreeComp;
};
