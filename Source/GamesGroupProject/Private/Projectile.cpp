#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

AProjectile::AProjectile()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetSimulatePhysics(true);
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Sphere->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
    Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    Sphere->SetNotifyRigidBodyCollision(true);
    


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 10.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle SmokeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(SmokeTimerHandle, this, &AProjectile::SpawnParticleEffect, 5.0f, false);

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AProjectile::DestroyProjectile, 10.0f, false);

}
void AProjectile::SpawnParticleEffect() const
{
	const FVector Location = GetActorLocation();
	if (ParticleEffect) 
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleEffect, Location, FRotator::ZeroRotator);
	if (Mesh) 
		Mesh->SetHiddenInGame(true);
}

void AProjectile::DestroyProjectile()
{
	Destroy();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AProjectile::Destroyed()
{
	Super::Destroyed();
	const FTransform SpawnTransform = GetActorTransform();
	if (SplashEffect)
        GetWorld()->SpawnActor<AActor>(SplashEffect, SpawnTransform);
}