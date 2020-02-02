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
	UPROPERTY(EditAnywhere, Category = "Body parts")
	EBodyPartSlot Slot;

	UPROPERTY(EditAnywhere, Category = "Body parts")
		int Strength;
	UPROPERTY(EditAnywhere, Category = "Body parts")
		int Dexterity;
	UPROPERTY(EditAnywhere, Category = "Body parts")
		int Constitution;
	UPROPERTY(EditAnywhere, Category = "Body parts")
		int Intelligence;

	UPROPERTY(EditAnywhere, Category = "Body parts")
		float BodyPartHealth;

	UPROPERTY(EditAnywhere, Category = "Body parts")
		class USkeletalMesh* Mesh;
	UPROPERTY(EditAnywhere, Category = "Body parts")
		class UMaterialInterface* Material;
};
