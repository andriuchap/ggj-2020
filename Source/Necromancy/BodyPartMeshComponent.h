// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "NecromancyTypes.h"
#include "BodyPartMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class NECROMANCY_API UBodyPartMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UBodyPartMeshComponent(const FObjectInitializer &ObjInitializer);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Body part")
	class UBodyPartData* Data;

public:
	EBodyPartSlot Slot;

	float BodyPartHealth;

	UBodyPartData* GetBodyPartData();

	void RefreshMesh();
};
