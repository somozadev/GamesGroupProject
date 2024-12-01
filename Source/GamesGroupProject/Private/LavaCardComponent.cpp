// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaCardComponent.h"

#include "AIEnemy.h"


// Sets default values for this component's properties
ULavaCardComponent::ULavaCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULavaCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULavaCardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULavaCardComponent::ActivateCard()
{
	return Super::ActivateCard();
}


bool ULavaCardComponent::UseCard(AActor* target)
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
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, FString::Printf(TEXT("Lava splash Created!")));
	return true;
}