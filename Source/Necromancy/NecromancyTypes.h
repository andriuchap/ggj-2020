// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NecromancyTypes.generated.h"

UENUM(BlueprintType)
enum class EBodyPartSlot : uint8
{
	BPS_Head,
	BPS_Body,
	BPS_LArm,
	BPS_RArm,
	BPS_Legs
};

UENUM()
enum class EDamageResult : uint8
{
	DR_DamageDealt,
	DR_Blocked,
	DR_LethalDamage
};

USTRUCT(BlueprintType)
struct FBodyPart
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Body part")
	class UBodyPartData* Data;
	UPROPERTY(BlueprintReadOnly, Category = "Body part")
	float Health;

	FBodyPart() : Data(NULL), Health(0) {}
	FBodyPart(UBodyPartData* InData);
};