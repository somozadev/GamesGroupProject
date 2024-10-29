// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCube.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"



// Sets default values
APlayerCube::APlayerCube()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// creation and set up of the spring arm for our character cube.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500;

	// Creation and set up of the camera that attaches to the spring arm.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	PlayerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerCube"));
	PlayerMeshComponent->SetupAttachment(RootComponent);

	DefaultTurningRate = 70.0f;
	

}	


// Called when the game starts or when spawned
void APlayerCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCube::MoveForward(float Value)
{
	if((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
		
	}
}

void APlayerCube::MoveRight(float Value)
{
	if((Controller) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
		
	}
}

void APlayerCube::TurningRate(float Value)
{
	AddControllerYawInput(Value * (float)DefaultTurningRate * GetWorld()->GetDeltaSeconds());
}

// Called every frame
void APlayerCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("Jump",IE_Pressed,this, &ACharacter::Jump);
	//PlayerInputComponent->BindAxis("Jump",IE_Released,this ,&ACharacter::StopJumping);

	//To Do List

	//Interact
	//Cancel
	//Card Select Left
	//Card Select Right
	//Hold Item
	//Shoot
	//Toggle Waypoint
	

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCube::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCube::MoveRight);

	// add input for looking up sightly.....

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurningRate", this, &APlayerCube::TurningRate);
	

}

