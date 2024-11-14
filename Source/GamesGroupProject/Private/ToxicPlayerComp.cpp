// Fill out your copyright notice in the Description page of Project Settings.


#include "ToxicPlayerComp.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
int NumberOfTargets=3;
// Sets default values for this component's properties
UToxicPlayerComp::UToxicPlayerComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}
APawn* pointto;
TArray<AActor*> FoundActors;
// Called when the game starts
void UToxicPlayerComp::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("Toxic Readied"));
	Super::BeginPlay();
	pointto = GetWorld()->GetFirstPlayerController()->GetPawn();
	// ...
}
void UToxicPlayerComp::ActivateToxin()
{
	UE_LOG(LogTemp, Warning, TEXT("Toxic Start"));
	TArray<float>Dists=TArray<float>();
	FVector selfpos = pointto->GetActorLocation();
	for (AActor* Actor : FoundActors)
	{
		FVector ActorLocation = Actor->GetActorLocation();
		float dist = FVector::Distance(selfpos,ActorLocation);
		Dists.Add(dist);
		UE_LOG(LogTemp, Warning, TEXT(" Checked for distance %f"),dist);
	}
	// while (NumberOfTargets > 0)
	// {
	// 	float distmin=0;
	// 	for (int i = 0; i < Dists.Num(); i++) {
	// 		if (Dists[i]<distmin) {
	// 			
	// 		}
	// 	}
	//
	// }
}
	// Called every frame
	void UToxicPlayerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		if (OnceTime)
		{
			ActivateToxin();
			OnceTime=false;
		}
	}


