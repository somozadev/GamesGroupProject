// Fill out your copyright notice in the Description page of Project Settings.


#include "ToxicCardNewest.h"
#include "AIEnemy.h"

void UToxicCardNewest::BeginPlay()
{
	Super::BeginPlay();
}

void UToxicCardNewest::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UToxicCardNewest::PrintToScreenIsSelected()
{
	Super::PrintToScreenIsSelected();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("CARD Poison ATTACK ")));
}

bool UToxicCardNewest::ActivateCard()
{
	return Super::ActivateCard();
}

bool UToxicCardNewest::UseCard(AActor* target)
{
	if (!Super::UseCard(target))
		return false;

	const AAIEnemy* Enemy = Cast<AAIEnemy>(target);
	if (!Enemy)
		return false;
	if (SplashObject)
	{
		const FVector Pos = Enemy->GetActorLocation();
		const FActorSpawnParameters SpawnParams;
		SplashSpawnedObject = GetWorld()->SpawnActor<AActor>(SplashObject, Pos, FRotator::ZeroRotator, SpawnParams);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Tox projectile Created!")));
		return true;
	}
	return false;
}

bool UToxicCardNewest::UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets)
{
	return Super::UseCard(target, otherTargets);
}
