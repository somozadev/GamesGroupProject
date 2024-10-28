// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GAMESGROUPPROJECT_API InventoryRowClass
{
/** Please add a struct description */
USTRUCT(BlueprintType)
struct FCardBaseLine
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="ID", MakeStructureDefaultValue="0"))
	int32 ID;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Name"))
	FString Name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Description"))
	FString Description;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Tags"))
	FString Tags;
};

public:
	InventoryRowClass();

	~InventoryRowClass();
};

