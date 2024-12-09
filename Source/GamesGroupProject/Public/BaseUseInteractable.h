// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "BaseUseInteractable.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API ABaseUseInteractable : public AInteractable
{
	GENERATED_BODY()

public:
	ABaseUseInteractable();

protected:
	virtual void BeginPlay() override;
	void Destroy();

	virtual void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp,
	                           int32 OtherBodyIndex) override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Interaction", meta = (EditInline = "true"))
	TSubclassOf<UUserWidget> Prompt;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Interaction")
	UUserWidget* ActivePromptWidget;
};
