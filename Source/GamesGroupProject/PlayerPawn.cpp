// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// player mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(Cast<USceneComponent>(MeshComponent));
	// camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	// follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	Speed = 500;
	Direction = FVector2D(0.f, 0.f);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		UE_LOG(LogTemp,Warning, TEXT("MoveForward: %f"),Value)
	}

	Direction.X = Value;
	/*FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, Value);*/
}

void APlayerPawn::MoveRight(float Value)
{
	if (Value != 0.0)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveForward: %f"), Value)
	}

	Direction.Y = Value;
	/*FVector Right = GetActorRightVector();
	AddMovementInput(Right, Value);*/
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	FVector DeltaLocation = FVector(Direction.X, Direction.Y, 0.f);
	DeltaLocation.Normalize();
	DeltaLocation *= Speed * DeltaTime;
	Location += DeltaLocation;

	SetActorLocation(Location);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);



}

