#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h" 
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/RotatingMovementComponent.h"

AInteractable::AInteractable()
{
	PrimaryActorTick.bCanEverTick = true;
	isCharmed = false;
	InContact = false;
	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerZone"));
	TriggerZone->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f)); //maybe expose the size
	TriggerZone->SetCollisionProfileName(TEXT("Trigger"));
	TriggerZone->SetupAttachment(RootComponent);
	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnTriggerEnter);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnTriggerExit);

	RotationMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation"));
	RotationMovement->bRotationInLocalSpace = true;
	RotationMovement->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	targetPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
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
	UE_LOG(LogTemp, Warning, TEXT("Object Handled!"));
}

void AInteractable::HandleCharm(AActor* interactorActor)
{
	isCharmed = true;
}

void AInteractable::HandleInstant(AActor* interactorActor)
{
	Destroy();
}

void AInteractable::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (useTriggers && OtherActor->IsA(APawn::StaticClass()))
	{
		PerformInteraction(OtherActor);
		InContact = true;
	}
}

void AInteractable::OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (useTriggers && OtherActor->IsA(APawn::StaticClass()))
	{
		InContact = false;
	}
}

