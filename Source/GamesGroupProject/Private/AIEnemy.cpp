// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "BaseAIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#define AWARENESS_DISTANCE 500.0f

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
	m_currentHealth = m_maxHealth;
	
	FVector location = GetActorLocation();

	m_controller = Cast<ABaseAIEnemyController>(GetController());
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint1"), m_patrolPoint1 + location);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint2"), m_patrolPoint2 + location);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint3"), m_patrolPoint3 + location);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint4"), m_patrolPoint4 + location);
	
	m_playerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	m_currentPatrolTarget = m_patrolPoint1;
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint1);
}

void AAIEnemy::ConsiderAttack()
{
	//TODO - Decision making for what attack to do. Will override in children
	int rng = rand() % 10;

	switch (rng)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		AttackA();
		break;
	case 5:
	case 6:
	case 7:
		AttackB();
		break;
	case 8:
	case 9:
		AttackC();
		break;
	default:
		break;
	}
}

//TO DO: Play animation and deal damage to player. Can be done once this branch is merged
void AAIEnemy::AttackA()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("I just did attack A")));
}

void AAIEnemy::AttackB()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("I just did attack B")));
}

void AAIEnemy::AttackC()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("I just did attack C")));
}

void AAIEnemy::CalculateNearestPatrolPoint()
{
	FVector pos = GetActorLocation();
	float firstDist = FVector::Dist(pos, m_patrolPoint1);
	float secondDist = FVector::Dist(pos, m_patrolPoint2);
	float thirdDist = FVector::Dist(pos, m_patrolPoint3);
	float fourthDist = FVector::Dist(pos, m_patrolPoint4);

	if (firstDist >= secondDist && firstDist >= thirdDist && firstDist >= fourthDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint1);
		m_nearestPatrolPoint = 1;
	}
	else if (secondDist >= firstDist && secondDist >= thirdDist && secondDist >= fourthDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint2);
		m_nearestPatrolPoint = 2;
	}
	else if (thirdDist >= firstDist && thirdDist >= secondDist && thirdDist >= fourthDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint3);
		m_nearestPatrolPoint = 3;
	}
	else if (fourthDist >= firstDist && fourthDist >= secondDist && fourthDist >= thirdDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint4);
		m_nearestPatrolPoint = 4;
	}
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_isAlive)
		return;

	if (!m_playerCharacter)
		m_playerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!m_playerCharacter)
		return;

	if (m_currentPatrolTarget == FVector(0))
	{
		m_currentPatrolTarget = m_patrolPoint1;
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint1);
	}

	if (FVector::Dist(GetActorLocation(), m_playerCharacter->GetActorLocation()) <= 500.0f)
	{
		m_isInChaseRange = true;
		m_controller->GetBlackboard()->SetValueAsBool(TEXT("IsInChaseRange"), true);
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("ChasePosition"), m_playerCharacter->GetActorLocation());
	}
	else
	{
		if (m_isInChaseRange)
		{
			CalculateNearestPatrolPoint();
		}
		m_isInChaseRange = false;
		m_controller->GetBlackboard()->SetValueAsBool(TEXT("IsInChaseRange"), false);

		if (FVector::Dist(GetActorLocation(), m_currentPatrolTarget) < 50.0f)
		{
			m_nearestPatrolPoint++;
			if (m_nearestPatrolPoint > 4)
				m_nearestPatrolPoint = 1;

			switch (m_nearestPatrolPoint)
			{
			case 1:
				m_currentPatrolTarget = m_patrolPoint1;
				break;
			case 2:
				m_currentPatrolTarget = m_patrolPoint2;
				break;
			case 3:
				m_currentPatrolTarget = m_patrolPoint3;
				break;
			case 4:
				m_currentPatrolTarget = m_patrolPoint4;
				break;
			default:
				break;
			}

			m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_currentPatrolTarget);
		}
	}
}

bool AAIEnemy::TakeDamage(int damage)
{
	m_currentHealth -= damage;
	//TO DO: Play death animation/deactivate if enemy dies
	return m_currentHealth <= 0;
}

bool AAIEnemy::GetIsAlive()
{
	return m_isAlive;
}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

