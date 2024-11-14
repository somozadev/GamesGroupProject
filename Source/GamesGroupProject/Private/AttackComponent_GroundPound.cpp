// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent_GroundPound.h"
#include "PlayerCube.h"
#include  "AIEnemy.h"
#include "PlayerHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

bool UAttackComponent_GroundPound::PerformAttack_Implementation(AActor* target, AActor* instigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Ground Pound!")));
	APlayerCube* player = Cast<APlayerCube>(target);
	AAIEnemy* enemy = Cast<AAIEnemy>(instigator);
	if (player != nullptr && enemy != nullptr)
	{
		FVector dir = player->GetActorLocation() - enemy->GetActorLocation();

		if (dir.Length() <= m_attackRadius)
		{
			UPlayerHealthComponent* healthComp = Cast<UPlayerHealthComponent>(player->GetComponentByClass(UPlayerHealthComponent::StaticClass()));
			if (healthComp != nullptr)
			{
				healthComp->TakeDamage(player, m_damage, 0, enemy->GetController(), enemy);
				UCharacterMovementComponent* moveComp = Cast<UCharacterMovementComponent>(player->GetMovementComponent());
				if (moveComp != nullptr)
				{
					FVector pushDir = FVector::UpVector;
					pushDir *= m_knockbackPower;
					moveComp->AddImpulse(pushDir, true);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Slam Hit!")));
					return true;
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Slam Missed")));
		}
	}
	return false;
}
