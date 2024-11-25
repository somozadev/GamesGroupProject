// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCube.h"

#include "AIEnemy.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Controller.h"
#include "CardComponent.h"



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
	DefaultLookUpRate = 45.0f;

	AttackDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	AttackDetectionSphere->InitSphereRadius(AimRadius);
	AttackDetectionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	AttackDetectionSphere->SetLineThickness(1);
	AttackDetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &APlayerCube::OnEnemyEnterRange);
	AttackDetectionSphere->OnComponentEndOverlap.AddDynamic(this, &APlayerCube::OnEnemyExitRange);

}	


// Called when the game starts or when spawned
void APlayerCube::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> components = GetComponentsByTag(UCardComponent::StaticClass(), FName("CardComp"));
	for (int i = 0; i < components.Num(); i++)
	{
		UCardComponent* cardComp = Cast<UCardComponent>(components[i]);
		if (cardComp)
		{
			CardList.Add(cardComp);
		}
	}
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



void APlayerCube::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * DefaultLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCube::TurningRate(float Value)
{
	AddControllerYawInput(Value * (float)DefaultTurningRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCube::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact input pressed"));
}

void APlayerCube::Cancel()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel input pressed"));
}

void APlayerCube::CardSelectLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("Card Select left input pressed"));
}

void APlayerCube::CardSelectRight()
{
	UE_LOG(LogTemp, Warning, TEXT("Card Select Right input pressed"));
}

void APlayerCube::HoldItem()
{
	UE_LOG(LogTemp, Warning, TEXT("HoldItem input pressed"));
}

void APlayerCube::DropHeldItem()
{
	UE_LOG(LogTemp, Warning, TEXT("DropHoldItem input pressed"));
}

void APlayerCube::Aim()
{
	UE_LOG(LogTemp, Warning, TEXT("Preparing Card"));
	//Check if card has ammo
	//Don't change to aiming stance if not
}

void APlayerCube::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("Shoot input pressed"));

	if (CardList.IsValidIndex(CurrentCard))
	{
		CardList[CurrentCard]->UseCard(TargetEnemy, TargetEnemiesInRange);
	}
}

void APlayerCube::StopShooting()
{
	UE_LOG(LogTemp, Warning, TEXT("StopShooting input pressed"));
}

void APlayerCube::ToggleWaypoint()
{
	UE_LOG(LogTemp, Warning, TEXT("Waypoint input pressed"));
}

void APlayerCube::Pause()
{
	UE_LOG(LogTemp, Warning, TEXT("Pause input pressed"));
}

void APlayerCube::OnEnemyEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor))
	{
		if(!TargetEnemiesInRange.Contains(Enemy))
		{
			TargetEnemiesInRange.Add(Enemy);

			if (TargetEnemy == nullptr)
			{
				TargetEnemy = TargetEnemiesInRange[0];
			}
		}
	}
}

void APlayerCube::OnEnemyExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor))
	{
		if(TargetEnemiesInRange.Contains(Enemy))
		{
			TargetEnemiesInRange.Remove(Enemy);

			if (Enemy->GetUniqueID() == TargetEnemy->GetUniqueID())
			{
				if (TargetEnemiesInRange.Num() == 0)
				{
					TargetEnemy = nullptr;
				}
				else
				{
					TargetEnemy = TargetEnemiesInRange[0];
				}
			}
		}
	}
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

	// Action Bindings for input actions.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCube::Interact);
	PlayerInputComponent->BindAction("Cancel", IE_Pressed, this, &APlayerCube::Cancel);
	// Card switching
	PlayerInputComponent->BindAction("CardSelectLeft", IE_Pressed, this, &APlayerCube::CardSelectLeft);
	PlayerInputComponent->BindAction("CardSelectRight", IE_Pressed, this, &APlayerCube::CardSelectRight);
	// Hold and drop items
	PlayerInputComponent->BindAction("HoldItem", IE_Pressed, this, &APlayerCube::HoldItem);
	PlayerInputComponent->BindAction("HoldItem" , IE_Released, this, &APlayerCube::DropHeldItem);
	// Shoot and stop shooting
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCube::Shoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerCube::StopShooting);
	
	//Toggle Waypoint
	PlayerInputComponent->BindAction("ToggleWaypoint", IE_Pressed, this, &APlayerCube::ToggleWaypoint);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCube::Pause);
	
	// Axis bindings for movement functions
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCube::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCube::MoveRight);

	
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurningRate", this, &APlayerCube::TurningRate);
	

}

