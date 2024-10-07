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

	if (FVector::Dist(GetActorLocation(), m_playerCharacter->GetActorLocation()) <= 500.0f)
	{
		m_controller->GetBlackboard()->SetValueAsBool(TEXT("IsInChaseRange"), true);
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("ChasePosition"), m_playerCharacter->GetActorLocation());
	}
	else
	{
		m_controller->GetBlackboard()->SetValueAsBool(TEXT("IsInChaseRange"), false);
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

