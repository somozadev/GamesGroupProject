


#include "SpawnerCardComponent.h"
#include "ObjectPoolingSystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USpawnerCardComponent::USpawnerCardComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	m_objectPool = Cast<AObjectPoolingSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), AObjectPoolingSystem::StaticClass()));
	m_attackObjectType = 0;
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
}

bool USpawnerCardComponent::ActivateCard()
{
	if (!Super::ActivateCard())
		return false;
}

bool USpawnerCardComponent::UseCard()
{
	Super::UseCard();

	return true;
}

bool USpawnerCardComponent::DeactivateCard()
{
	Super::DeactivateCard();
	return true;
}

