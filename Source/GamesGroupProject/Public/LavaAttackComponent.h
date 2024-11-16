#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCube.h"
#include "Components/SphereComponent.h"
#include "AIEnemy.h"
#include "LavaAttackComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API ULavaAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULavaAttackComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnEnemyEnterRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEnemyExitRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	FVector TargetLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Lava Attack")
	TSubclassOf<AActor> SplashObject;

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	AActor* SplashSpawnedObject;

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	TArray<AAIEnemy*> TargetEnemiesInRange;

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	AAIEnemy* TargetEnemy;

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	APlayerCube* PlayerCube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lava Attack")
	float AimRadius;

	UPROPERTY(VisibleAnywhere, Category = "Lava Attack")
	USphereComponent* DetectionSphere;

	int32 CurrentTargetIndex;

public:
	void StartAiming();
	void StopAiming();
	void UseAttack();
	void CreateTargetObject();
	void MoveLeft();
	void MoveRight();
	void SetCurrentTarget();
};
