#pragma once

#include "CoreMinimal.h"
#include "BaseUseInteractable.h"
#include "BaseDoor.generated.h"

UCLASS()
class GAMESGROUPPROJECT_API ABaseDoor : public ABaseUseInteractable
{
	GENERATED_BODY()

public:
	ABaseDoor();
	UFUNCTION(BlueprintCallable, Category = "Door")
	void WhenDoorOpened();
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnDoorOpened_BP();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	bool IsOpen;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void InteractInputTriggerToUse();
	UFUNCTION()
	void UnlockDoor();
};
