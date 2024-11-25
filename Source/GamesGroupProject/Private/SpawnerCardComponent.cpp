


#include "SpawnerCardComponent.h"

#include "AIEnemy.h"
#include "ObjectPoolingSystem.h"
#include "PlayerCube.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USpawnerCardComponent::USpawnerCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//UCardComponent();
	m_player = Cast<APlayerCube>(GetOwner());
	m_targetIndex = -1;
	
	m_objectPool = Cast<AObjectPoolingSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), AObjectPoolingSystem::StaticClass()));
	m_attackObjectType = 0;

	if (m_player != nullptr)
	{
		TArray<UActorComponent*> comps = m_player->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("Reticle"));
		if (comps.Num() > 0)
			m_targetReticle = Cast<UStaticMeshComponent>(comps[0]);
		else
			m_targetReticle = nullptr;
	}
	else
		m_targetReticle = nullptr;
}


// Called when the game starts
void USpawnerCardComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnerCardComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (m_target != nullptr && m_targetReticle != nullptr && m_targetIndex > -1)
	{
		m_targetReticle->SetWorldLocation(m_target->GetActorLocation());
	}
}

bool USpawnerCardComponent::ActivateCard()
{
	if (!Super::ActivateCard())
		return false;

	return true;
}

bool USpawnerCardComponent::UseCard()
{
	Super::UseCard();

	return true;
}

bool USpawnerCardComponent::UseCard(AActor* target)
{
	return Super::UseCard(target);
}

bool USpawnerCardComponent::UseCard(AActor* target, TArray<AAIEnemy*>& otherTargets)
{
	return Super::UseCard(target, otherTargets);
}

bool USpawnerCardComponent::DeactivateCard()
{
	Super::DeactivateCard();
	return true;
}

