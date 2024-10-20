// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIEnemyController.h"
#include "AIEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

ABaseAIEnemyController::ABaseAIEnemyController()
{
	m_blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(m_blackboard);

	m_behaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(m_behaviorTreeComp);
}

void ABaseAIEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr)
	{
		return;
	}

	AAIEnemy* enemy = Cast<AAIEnemy>(InPawn);
	if (enemy)
	{
		if (enemy->m_behaviorTree)
		{
			m_blackboard->InitializeBlackboard(*(enemy->m_behaviorTree->BlackboardAsset));
			m_behaviorTreeComp->StartTree(*(enemy->m_behaviorTree));
		}
	}
}

UBlackboardComponent* ABaseAIEnemyController::GetBlackboard()
{
	return m_blackboard;
}
