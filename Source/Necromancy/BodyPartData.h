// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NecromancyTypes.h"
#include "BodyPartData.generated.h"

UCLASS()
class NECROMANCY_API UBodyPartData : public UDataAsset
{
	GENERATED_BODY()
public:
	UBodyPartData(const FObjectInitializer &ObjInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
	EBodyPartSlot Slot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		int Strength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		int Dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		int Constitution;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		int Intelligence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		float BodyPartHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		class USkeletalMesh* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Body parts")
		class UMaterialInterface* Material;
};
