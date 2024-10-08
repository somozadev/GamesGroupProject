// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskAttack.h"
#include "AIEnemy.h"
#include "AIController.h"

EBTNodeResult::Type UBTTaskAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	AAIEnemy* ownerActor = Cast<AAIEnemy>(controller->GetPawn());

	if (!ownerActor)
		return EBTNodeResult::Aborted;

	ownerActor->ConsiderAttack();

	return EBTNodeResult::Succeeded;
}
