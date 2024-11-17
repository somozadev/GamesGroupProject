#include "LavaAttackComponent.h"
#include "DrawDebugHelpers.h"
#include "PlayerCube.h"
#include "Engine/World.h"
#include "AIEnemy.h"
#include "EventsManager.h"
#include "Components/SphereComponent.h"

ULavaAttackComponent::ULavaAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsAiming = false;
	CurrentTargetIndex = -1;
	AimRadius = 1000.0f;

	// Defer attaching to avoid null root component
	DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	DetectionSphere->InitSphereRadius(AimRadius);
	DetectionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	DetectionSphere->SetLineThickness(1);
	DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ULavaAttackComponent::OnEnemyEnterRange);
	DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ULavaAttackComponent::OnEnemyExitRange);

}


void ULavaAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCube = Cast<APlayerCube>(GetOwner());
	if (PlayerCube)
	{
        DetectionSphere->AttachToComponent(PlayerCube->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DetectionSphere->SetRelativeLocation(FVector::ZeroVector);
	}
}

void ULavaAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULavaAttackComponent::StartAiming() //called on LavaCard selected 
{
	bIsAiming = true;
	SetCurrentTarget();
	
}

void ULavaAttackComponent::StopAiming()
{
	bIsAiming = false;
	TargetEnemy = nullptr;
	// TargetEnemiesInRange.Empty();
	CurrentTargetIndex = -1;
}

void ULavaAttackComponent::UseAttack() //called on shoot after lavacard selected
{
	CreateTargetObject();
	StopAiming();
}

void ULavaAttackComponent::CreateTargetObject()
{
	if (PlayerCube && TargetEnemy && SplashObject)
	{
		FVector pos = TargetEnemy->GetActorLocation();
		// const FVector SpawnLocation = FVector(pos.X, pos.Y, 0);
		const FActorSpawnParameters SpawnParams;
		SplashSpawnedObject = GetWorld()->SpawnActor<AActor>(SplashObject, pos, FRotator::ZeroRotator, SpawnParams);
	}
}

void ULavaAttackComponent::SetCurrentTarget()
{
	if (TargetEnemiesInRange.Num() > 0)
	{
		if (CurrentTargetIndex == -1 || CurrentTargetIndex >= TargetEnemiesInRange.Num())
		{
			CurrentTargetIndex = 0;
		}
		TargetEnemy = TargetEnemiesInRange[CurrentTargetIndex];

		//can't rotate player as camera has prio and keeps locking BP_PlayerCube Z rotation... ideas?
		
		// if (TargetEnemy && PlayerCube)
		// {
		// 	FVector DirectionToTarget = (TargetEnemy->GetActorLocation() - PlayerCube->GetActorLocation()).GetSafeNormal();
		// 	FRotator LookAtRotation = DirectionToTarget.Rotation();
		// 	LookAtRotation.Pitch = 0.0f;
		// 	LookAtRotation.Roll = 0.0f;
		// 	PlayerCube->SetActorRotation(LookAtRotation);
		// }
	}
	else
	{
		CurrentTargetIndex = -1;
		TargetEnemy = nullptr;
	}
}

void ULavaAttackComponent::MoveLeft() //should be called on player inputs left on right trigger
{
	if (TargetEnemiesInRange.Num() > 0)
	{
		CurrentTargetIndex = (CurrentTargetIndex - 1 + TargetEnemiesInRange.Num()) % TargetEnemiesInRange.Num();
		SetCurrentTarget();
	}
}

void ULavaAttackComponent::MoveRight() //should be called on player inputs right on right trigger
{
	if (TargetEnemiesInRange.Num() > 0)
	{
		CurrentTargetIndex = (CurrentTargetIndex + 1) % TargetEnemiesInRange.Num();
		SetCurrentTarget();
	}
}

void ULavaAttackComponent::OnEnemyEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor))
	{
		if(!TargetEnemiesInRange.Contains(Enemy))
			TargetEnemiesInRange.Add(Enemy);
	}
}

void ULavaAttackComponent::OnEnemyExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor))
	{
		if(TargetEnemiesInRange.Contains(Enemy))
			TargetEnemiesInRange.Remove(Enemy);
	}
}