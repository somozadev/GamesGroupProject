// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerHealthComponent.h"
#include "PlayerCube.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UInputAction;
class USphereComponent;
class AAIEnemy;
class UCardComponent;

UCLASS()
class GAMESGROUPPROJECT_API APlayerCube : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCube();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "PlayerCube")
	UStaticMeshComponent* PlayerMeshComponent;

	void Interact();
	void Cancel();
	void CardSelectLeft();
	void CardSelectRight();
	void HoldItem();
	void DropHeldItem();
	void Aim();
	void Shoot();
	void StopShooting();
	void ToggleWaypoint();
	void Pause();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpRate(float Value);
	void TurningRate(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	float DefaultTurningRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	float DefaultLookUpRate;

	USphereComponent* AttackDetectionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "AttackDetection")
	float AimRadius = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "AttackDetection")
	TArray<AAIEnemy*> TargetEnemiesInRange;

	AAIEnemy* TargetEnemy = nullptr;

	TArray<UCardComponent*> CardList;
	int CurrentCard = 0;

	UFUNCTION()
	void OnEnemyEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						  int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
