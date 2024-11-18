#include "LavaAttackSplash.h"
#include "AIEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ALavaAttackSplash::ALavaAttackSplash()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	DamageArea = CreateDefaultSubobject<USphereComponent>(TEXT("DamageArea"));
	DamageArea->SetupAttachment(DefaultSceneRoot);
	DamageArea->SetSphereRadius(300.0f);
	DamageArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	DamageArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Visuals = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visuals"));
	Visuals->SetupAttachment(DefaultSceneRoot);

	Visuals->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Visuals->SetCollisionResponseToAllChannels(ECR_Ignore);

	DamageArea->OnComponentBeginOverlap.AddDynamic(this, &ALavaAttackSplash::OnOverlapBegin);
	DamageArea->OnComponentEndOverlap.AddDynamic(this, &ALavaAttackSplash::OnOverlapEnd);
	ElapsedSplashDuration = 0.0f;
}

void ALavaAttackSplash::BeginPlay()
{
	Super::BeginPlay();
}

void ALavaAttackSplash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedSplashDuration += DeltaTime;
	ElapsedToTickDmgSplashDuration += DeltaTime;
	if (ElapsedToTickDmgSplashDuration >= SplashTickDamageDuration)
	{
		for (AAIEnemy* Enemy : EnemiesInSplash)
			if (Enemy)
				Enemy->TakeAttackDamage(Damage);
	}
	if (ElapsedSplashDuration >= SplashDuration)
		Destroy(); //use obj pooling system here
}

void ALavaAttackSplash::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                       bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor))
	{
		EnemiesInSplash.AddUnique(Enemy);
	}
}

void ALavaAttackSplash::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AAIEnemy* Enemy = Cast<AAIEnemy>(OtherActor))
	{
		EnemiesInSplash.Remove(Enemy);
	}
}
