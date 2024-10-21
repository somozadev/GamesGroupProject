// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent_Pushback.h"
#include "PlayerCube.h"
#include  "AIEnemy.h"
#include "PlayerHealthComponent.h"
#include "Components/CapsuleComponent.h"

UAttackComponent_Pushback::UAttackComponent_Pushback()
{
	m_damage = 1.0f;
	m_knockbackPower = 100.0f;
}

bool UAttackComponent_Pushback::PerformAttack_Implementation(AActor* target, AActor* instigator)
{
	APlayerCube* player = Cast<APlayerCube>(target);
	AAIEnemy* enemy = Cast<AAIEnemy>(instigator);

	if (player != nullptr && enemy != nullptr)
	{
		UPlayerHealthComponent* healthComp = Cast<UPlayerHealthComponent>(player->GetComponentByClass(UPlayerHealthComponent::StaticClass()));
		if (healthComp != nullptr)
		{
			healthComp->TakeDamage(player, m_damage, 0, enemy->GetController(), enemy);
			UCapsuleComponent* mesh = Cast<UCapsuleComponent>(player->GetRootComponent());
			if (mesh != nullptr)
			{
				FVector dir = player->GetActorLocation() - enemy->GetActorLocation();
				dir.Normalize();
				dir *= m_knockbackPower;
				mesh->AddImpulse(dir);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Push Attack!")));
				return true;
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, FString::Printf(TEXT("Something went wrong!")));
	return false;
}
