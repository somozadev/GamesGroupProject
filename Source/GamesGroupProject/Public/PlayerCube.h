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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurningRate(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	float DefaultTurningRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
