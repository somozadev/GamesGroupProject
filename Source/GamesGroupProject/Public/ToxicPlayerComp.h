// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToxicPlayerComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMESGROUPPROJECT_API UToxicPlayerComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UToxicPlayerComp();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attributes);
	UClass* TargetClass;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool OnceTime=true;
	void ActivateToxin();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
