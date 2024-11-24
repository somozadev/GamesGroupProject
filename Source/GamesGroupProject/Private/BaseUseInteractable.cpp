#include "EventsManager.h"
#include "Blueprint/UserWidget.h"
#include "BaseUseInteractable.h"


ABaseUseInteractable::ABaseUseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;
	interactionType = EInteractionType::EIT_Use;
	
}

void ABaseUseInteractable::BeginPlay()
{
	Super::BeginPlay();
}


void ABaseUseInteractable::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	Super::OnTriggerEnter(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (useTriggers && OtherActor->IsA(APawn::StaticClass()))
	{
		if (Prompt)
		{
			if (ActivePromptWidget == nullptr)
			{
				ActivePromptWidget = CreateWidget<UUserWidget>(Cast<APlayerController>(OtherActor->GetOwner()), Prompt);
			}

			if (ActivePromptWidget && !ActivePromptWidget->IsInViewport())
			{
				ActivePromptWidget->AddToViewport();
			}
		}
	}
}

void ABaseUseInteractable::OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnTriggerExit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	if (ActivePromptWidget && ActivePromptWidget->IsInViewport())
	{
		ActivePromptWidget->RemoveFromParent();
		ActivePromptWidget = nullptr;
	}
}

void ABaseUseInteractable::Destroy()
{
	if (ActivePromptWidget && ActivePromptWidget->IsInViewport())
	{
		ActivePromptWidget->RemoveFromParent();
	}

	Super::Destroy();
}
