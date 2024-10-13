// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()
	/** mesh component giving our player a visual representation of a cube
	in the world */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MeshComponent;

	/** camera boom to position the camera behind the pawn */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow Camera  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	
	/** speed to scale movement by */
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float Speed;*/

	/** Store X and Y components of pawns direction */
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D Direction;*/

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called for forward and backwards player movement
	void MoveForward(float Value);
	// Called for right and left player movement
	void MoveRight(float Value);
	// Called for looking up
	void LookUp(float Value);
	// Called for rotation
	void Rotate(float Value);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
