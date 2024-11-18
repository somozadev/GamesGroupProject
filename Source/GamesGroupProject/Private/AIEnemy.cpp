// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemy.h"
#include "BaseAIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "PlayerHealthComponent.h"
#include "AttackComponent_MultiHit.h"

#define AWARENESS_DISTANCE 500.0f

// Sets default values
AAIEnemy::AAIEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_warningMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Warning Mesh"));
	m_warningMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_warningMesh->SetVisibility(false);
	m_warningMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();
	m_currentHealth = m_maxHealth;
	
	FVector location = GetActorLocation();

	m_patrolPoint1 += location;
	m_patrolPoint2 += location;
	m_patrolPoint3 += location;
	m_patrolPoint4 += location;

	m_controller = Cast<ABaseAIEnemyController>(GetController());
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint1"), m_patrolPoint1);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint2"), m_patrolPoint2);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint3"), m_patrolPoint3);
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolPoint4"), m_patrolPoint4);
	
	m_playerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	m_currentPatrolTarget = m_patrolPoint1;
	m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint1);
	m_controller->GetBlackboard()->SetValueAsBool(TEXT("IsInChaseRange"), false);

	TArray<UActorComponent*> components = GetComponentsByTag(UAttackComponent::StaticClass(), FName("AttackComp"));
	for (int i = 0; i < components.Num(); i++)
	{
		UAttackComponent* attackComp = Cast<UAttackComponent>(components[i]);
		if (attackComp)
		{
			m_attackComponents.Add(attackComp);
		}
	}
}

void AAIEnemy::ConsiderAttack()
{
	//TODO - Decision making for what attack to do. Will override in children
	//Will do this in children rather than in base class. Base will just default to the first attack if it exists

	if (!m_isAlive)
		return;
	
	if (m_timeSinceLastAttack < m_attackCooldown)
		return;

	if (m_multihitTimer > 0.0f)
		return;

	if (GetWorld()->GetTimerManager().GetTimerRemaining(m_timerHandle) > 0.0f)
		return;

	if (m_attackComponents.Num() == 0)
		return;

	int rng = rand() % m_attackComponents.Num();

	if (m_attackComponents.IsValidIndex(rng))
	{
		if (m_attackComponents[rng] != nullptr)
		{
			if (m_attackComponents[rng]->GetIsDelayed())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Delayed Attack")));
				m_timerDelegate.BindUFunction(this, "PerformDelayedAttack", rng);
				GetWorld()->GetTimerManager().SetTimer(m_timerHandle, m_timerDelegate, m_attackComponents[rng]->GetDelayTime(), false);
				if (m_attackComponents[rng]->GetAttackRadius() > 0.0f)
				{
					m_warningMesh->SetVisibility(true);
					m_warningMesh->SetWorldScale3D(FVector(m_attackComponents[rng]->GetAttackRadius() / 50.0f, m_attackComponents[rng]->GetAttackRadius() / 50.0f, 0.1f));

					UAttackComponent_MultiHit* multiHit = Cast<UAttackComponent_MultiHit>(m_attackComponents[rng]);

					if (IsValid(multiHit))
					{
						m_multihitTimer = multiHit->GetCombinedDelayTimes();
						m_currentMultiIndex = rng;
					}
				}
			}
			else
			{
				m_attackComponents[rng]->PerformAttack(m_playerCharacter, this);
			}
		}
	}

	m_timeSinceLastAttack = 0.0f;
}

void AAIEnemy::CalculateNearestPatrolPoint()
{
	FVector pos = GetActorLocation();
	float firstDist = FVector::Dist(pos, m_patrolPoint1);
	float secondDist = FVector::Dist(pos, m_patrolPoint2);
	float thirdDist = FVector::Dist(pos, m_patrolPoint3);
	float fourthDist = FVector::Dist(pos, m_patrolPoint4);

	if (firstDist <= secondDist && firstDist <= thirdDist && firstDist <= fourthDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint1);
		m_currentPatrolTarget = m_patrolPoint1;
		m_nearestPatrolPoint = 1;
	}
	else if (secondDist <= firstDist && secondDist <= thirdDist && secondDist <= fourthDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint2);
		m_currentPatrolTarget = m_patrolPoint2;
		m_nearestPatrolPoint = 2;
	}
	else if (thirdDist <= firstDist && thirdDist <= secondDist && thirdDist <= fourthDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint3);
		m_currentPatrolTarget = m_patrolPoint3;
		m_nearestPatrolPoint = 3;
	}
	else if (fourthDist <= firstDist && fourthDist <= secondDist && fourthDist <= thirdDist)
	{
		m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint4);
		m_currentPatrolTarget = m_patrolPoint4;
		m_nearestPatrolPoint = 4;
	}
}

void AAIEnemy::PerformDelayedAttack(int index)
{
	if (m_attackComponents.IsValidIndex(index))
	{
		if (m_attackComponents[index] != nullptr)
		{
			m_attackComponents[index]->PerformAttack(m_playerCharacter, this);
			m_warningMesh->SetVisibility(false);
			UAttackComponent_MultiHit* multiHit = Cast<UAttackComponent_MultiHit>(m_attackComponents[index]);

			if (IsValid(multiHit))
			{
				m_multihitTimer = multiHit->GetCombinedDelayTimes();
				m_currentMultiIndex = index;
			}
		}
	}
}

void AAIEnemy::UpdateMultiHitWarning()
{
	if (IsValid(m_warningMesh) && m_attackComponents.IsValidIndex(m_currentMultiIndex))
	{
		UAttackComponent_MultiHit* multiHit = Cast<UAttackComponent_MultiHit>(m_attackComponents[m_currentMultiIndex]);
		if (IsValid(multiHit))
		{
			m_warningMesh->SetVisibility(true);
			m_warningMesh->SetWorldScale3D(FVector(multiHit->GetCurrentRadius() / 50.0f, multiHit->GetCurrentRadius() / 50.0f, 0.1f));
		}
	}
}

// Called every frame
void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_isAlive)
		return;

	if (m_multihitTimer > 0.0f)
	{
		m_multihitTimer -= DeltaTime;
		//Hides the warning symbol after last mulkti hit
		if (m_multihitTimer <= 0.0f)
		{
			m_warningMesh->SetVisibility(false);
		}
	}
		

	if (GetWorld()->GetTimerManager().GetTimerRemaining(m_timerHandle) > 0.0f)
		return;

	if (m_multihitTimer > 0.0f)
	{
		UpdateMultiHitWarning();
		return;
	}

	if (!m_playerCharacter)
		m_playerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!m_playerCharacter)
		return;

	m_timeSinceLastAttack += DeltaTime;

	//m_controller->GetBlackboard()->SetValueAsVector(TEXT("PatrolTarget"), m_patrolPoint1);

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
		float dist = FVector::Dist(GetActorLocation(), m_currentPatrolTarget);

		if (dist <= 50.0f)
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

bool AAIEnemy::TakeAttackDamage(int damage)
{
	m_currentHealth -= damage;

	if (m_currentHealth <= 0)
	{
		m_isAlive = false;
		m_controller->BrainComponent->StopLogic(FString("Enemy Dead"));
		PrimaryActorTick.bCanEverTick = false;
		m_warningMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		m_warningMesh->SetVisibility(false);
		SetActorEnableCollision(false);
		GetMesh()->SetVisibility(false);
	}
		
	//TO DO: Play death animation/deactivate if enemy dies
	return m_currentHealth <= 0;
}

bool AAIEnemy::GetIsAlive()
{
	return m_isAlive;
}

float AAIEnemy::GetCurrentHealth()
{
	return m_currentHealth;
}

float AAIEnemy::GetMaxHealth()
{
	return m_maxHealth;
}

// Called to bind functionality to input
void AAIEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

