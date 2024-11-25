

#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "EventManager.h"
#include <Kismet/GameplayStatics.h>
#include <string>
#include <EventsManager.h>

AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = true;
	isCharmed = false; 
	
	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	TriggerZone->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));  //maybe expose the size
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
	TriggerZone->SetupAttachment(RootComponent); 
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnTriggerEnter);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnTriggerExit);

}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	targetPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AInteractable::ExampleEventUsage()
{
	UE_LOG(LogTemp, Warning, TEXT("Event called and method invoked!"));
}

void AInteractable::PerformInteraction(AActor* interactorActor)
{
	switch (interactionType)
	{
	case EInteractionType::EIT_Pickup:
		HandlePickup(interactorActor);
		break;
	case EInteractionType::EIT_Use:
		HandleUse(interactorActor);
		break;
	case EInteractionType::EIT_Charm:
		HandleCharm(interactorActor);
		break;
	case EInteractionType::EIT_Instant:
		HandleInstant(interactorActor);
		break;
	default:
		break;
	}
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isCharmed && targetPlayer)
	{
		FVector Direction = (targetPlayer->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + Direction * charmedSpeed * GetWorld()->DeltaTimeSeconds;
		SetActorLocation(NewLocation);
		if (FVector::Dist(GetActorLocation(), targetPlayer->GetActorLocation()) < 100.0f)
		{
			HandlePickup(this);
			isCharmed = false;
		}
	}
}

void AInteractable::Interact(AActor* interactorActor)
{
	PerformInteraction(interactorActor);
}

void AInteractable::HandlePickup(AActor* interactorActor)
{
	Destroy();
}

void AInteractable::HandleUse(AActor* interactorActor)
{

	//trigger bp to show player Wb_interactbutton

	UE_LOG(LogTemp, Warning, TEXT("Object Handled!"));
	// Destroy();
}

void AInteractable::HandleCharm(AActor* interactorActor)
{
	isCharmed = true;
}

void AInteractable::HandleInstant(AActor* interactorActor)
{    
	// need object method as well as players currency holding (in inventory)
	UE_LOG(LogTemp, Warning, TEXT("Instant interaction occurred!"));
	Destroy();
}

void AInteractable::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (useTriggers && OtherActor->IsA(APawn::StaticClass()))
	{
		PerformInteraction(OtherActor);
	}
}

void AInteractable::OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

