#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.h"
#include "EnemyDropsComponent.generated.h"

UENUM(BlueprintType)
enum class ECardDropType : uint8
{
	Combat UMETA(DisplayName = "Combat"),
	Puzzle UMETA(DisplayName = "Puzzle")
};

UENUM(BlueprintType)
enum class ELevel : uint8
{
	Level1 UMETA(DisplayName = "Level 1"),
	Level2 UMETA(DisplayName = "Level 2"),
	Level3 UMETA(DisplayName = "Level 3")
};

UENUM(BlueprintType)
enum class EGroup : uint8
{
	Probability UMETA(DisplayName = "Probability Based"),
	Group1 UMETA(DisplayName = "Group 1"),
	Group2 UMETA(DisplayName = "Group 2"),
	Group3 UMETA(DisplayName = "Group 3"),
	Group4 UMETA(DisplayName = "Group 4"),
	Group5 UMETA(DisplayName = "Group 5"),
	Group6 UMETA(DisplayName = "Group 6"),
	Group7 UMETA(DisplayName = "Group 7"),
	Group8 UMETA(DisplayName = "Group 8"),
	Group9 UMETA(DisplayName = "Group 9"),
	Group10 UMETA(DisplayName = "Group 10"),
	Group11 UMETA(DisplayName = "Group 11"),
};

USTRUCT(BlueprintType)
struct FDropItems
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Acorns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Lava;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Thunder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Toxin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Balance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Invincibility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Floating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Magnetism;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Laser;

	FDropItems() : Acorns(0), Lava(0), Thunder(0), Toxin(0), Balance(0), Invincibility(0), Floating(0), Magnetism(0),
		Laser(0)
	{
	}

	FDropItems(int32 InAcorns, int32 InLava, int32 InThunder, int32 InToxin, int32 InBalance, int32 InInvincibility,
		int32 InFloating, int32 InMagnetism, int32 InLaser)
		: Acorns(InAcorns), Lava(InLava), Thunder(InThunder), Toxin(InToxin), Balance(InBalance),
		Invincibility(InInvincibility), Floating(InFloating), Magnetism(InMagnetism), Laser(InLaser)
	{
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMESGROUPPROJECT_API UEnemyDropsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	ECardDropType dropType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	ELevel Level;

	UFUNCTION(BlueprintCallable, Category = "Drops")
	void Drop();
	UEnemyDropsComponent();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> acornBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> lavaBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> thunderBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> toxinBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> balanceBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> invincibilityBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> floatingBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> magnetismBP;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AInteractable> laserBP;


protected:
	virtual void BeginPlay() override;
	float minRandomSpawnRadius;
	float maxRandomSpawnRadius;

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	void SpawnDroppedElement(TSubclassOf<AInteractable> spawnable);

	EGroup Group;
	void SpawnItems(const FDropItems& Items);
	static FDropItems GetProbabilityDrop(ECardDropType CardDropType, ELevel Level);
	void OnItemsDropped();



public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;
};