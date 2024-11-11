// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent_MultiHit.h"
#include "PlayerHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UAttackComponent_MultiHit::PerformAttack_Implementation(AActor* target, AActor* instigator)
{
	if (m_isAttacking)
		return false;

	m_isAttacking = true;
	m_attackPhase = 0;
	m_player = Cast<APlayerCube>(target);
	m_enemy = Cast<AAIEnemy>(instigator);

	if (m_player != nullptr && m_enemy != nullptr)
	{
		FVector dir = m_player->GetActorLocation() - m_enemy->GetActorLocation();

		if (dir.Length() <= m_attackRadius)
		{
			UPlayerHealthComponent* healthComp = Cast<UPlayerHealthComponent>(m_player->GetComponentByClass(UPlayerHealthComponent::StaticClass()));
			if (healthComp != nullptr)
			{
				healthComp->TakeDamage(m_player, m_damage, 0, m_enemy->GetController(), m_enemy);
				UCharacterMovementComponent* moveComp = Cast<UCharacterMovementComponent>(m_player->GetMovementComponent());
				if (moveComp != nullptr)
				{
					//FVector dir = m_player->GetActorLocation() - m_enemy->GetActorLocation();
					dir += FVector(0.0f,0.0f,m_knockbackHeight);
					dir.Normalize();
					dir *= m_knockbackPower;
					moveComp->AddImpulse(dir, true);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Push Attack!")));
					return true;
				}
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Something went wrong!")));
	return false;
}

void UAttackComponent_MultiHit::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_isAttacking)
	{
		m_currentAttackTime += DeltaTime;

		if (m_multiAttackTimings.IsValidIndex(m_attackPhase) && m_multiAttackRadius.IsValidIndex(m_attackPhase) && m_multiAttackDamage.IsValidIndex(m_attackPhase) &&
			m_multiAttackKnockbackHeight.IsValidIndex(m_attackPhase) && m_multiAttackKnockbackPower.IsValidIndex(m_attackPhase) &&
			m_player != nullptr && m_enemy != nullptr)
		{
			if (m_currentAttackTime >= m_multiAttackTimings[m_attackPhase])
			{
				FVector dir = m_player->GetActorLocation() - m_enemy->GetActorLocation();

				if (dir.Length() <= m_multiAttackRadius[m_attackPhase])
				{
					UPlayerHealthComponent* healthComp = Cast<UPlayerHealthComponent>(m_player->GetComponentByClass(UPlayerHealthComponent::StaticClass()));
					if (healthComp != nullptr)
					{
						healthComp->TakeDamage(m_player, m_multiAttackDamage[m_attackPhase], 0, m_enemy->GetController(), m_enemy);
						UCharacterMovementComponent* moveComp = Cast<UCharacterMovementComponent>(m_player->GetMovementComponent());
						if (moveComp != nullptr)
						{
							//FVector dir = m_player->GetActorLocation() - m_enemy->GetActorLocation();
							dir += FVector(0.0f,0.0f,m_multiAttackKnockbackHeight[m_attackPhase]);
							dir.Normalize();
							dir *= m_multiAttackKnockbackPower[m_attackPhase];
							moveComp->AddImpulse(dir, true);
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Multi Attack!")));
							m_attackPhase++;

							if (m_attackPhase >= m_multiAttackTimings.Num())
							{
								GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Attack Over!")));
								m_isAttacking = false;
							}
						}
					}
				}
			}
		}
		else
		{
			m_isAttacking = false;
		}
	}
}

float UAttackComponent_MultiHit::GetCombinedDelayTimes()
{
	float total = 0.0f;

	for (int i = 0; i < m_multiAttackTimings.Num(); i++)
	{
		if (m_multiAttackTimings.IsValidIndex(i))
			total += m_multiAttackTimings[i];
	}

	return total;
}
