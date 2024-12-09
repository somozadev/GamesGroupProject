// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	EIT_Pickup UMETA(DisplayName = "Pickup"),
	EIT_Use UMETA(DisplayName = "Use"),
	EIT_Charm UMETA(DisplayName = "Charm"),
	EIT_Instant UMETA(DisplayName = "Instant")
};


UCLASS()
class GAMESGROUPPROJECT_API AInteractable : public AActor
	//it might need to inherit from a object class, or just add here the actual object_id and so on of it.. based on inventory mostly to decide
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PerformInteraction(AActor* interactorActor);
	virtual void HandlePickup(AActor* interactorActor);
	virtual void HandleUse(AActor* interactorActor);
	UFUNCTION()
	virtual void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                           UPrimitiveComponent* OtherComp,
	                           int32 OtherBodyIndex);
	APawn* targetPlayer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent* RotationMovement;
public:
	// Called every frame
	

	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact(AActor* interactorActor);
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void HandleCharm(AActor* interactorActor);
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void HandleInstant(AActor* interactorActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	EInteractionType interactionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool useTriggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction")
	float charmedSpeed = 600.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	bool InContact;

private:
	//As this type of interactions are not 100% defined yet, this code will remain as so. Once it's done, better approach to virtualize HandleInteraction and each type, with it's own class, handles it's own interaction.
	bool isCharmed{false};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerZone;
};
