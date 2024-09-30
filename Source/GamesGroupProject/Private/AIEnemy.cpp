// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "BaseAIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AAIEnemy::AAIEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	FVector location = GetActorLocation();

	m_controller = Cast<ABaseAIEnemyController>(GetController());
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint1"), m_patrolPoint1 + location);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint2"), m_patrolPoint2 + location);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint3"), m_patrolPoint3 + location);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint4"), m_patrolPoint4 + location);
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

