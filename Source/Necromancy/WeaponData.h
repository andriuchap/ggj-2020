// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class NECROMANCY_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
public:
	UWeaponData(const FObjectInitializer &ObjInitializer);

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		class UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		class UMaterialInterface* WeaponMaterial;
};
