// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NecromancyTypes.h"
#include "NecromancerController.generated.h"

UCLASS()
class NECROMANCY_API ANecromancerController : public APlayerController
{
	GENERATED_BODY()
public:
	ANecromancerController(const FObjectInitializer &ObjInitializer);

public:
	int ScrapFlesh;

	TArray<FBodyPart> AvailableParts;

	TMap<EBodyPartSlot, FBodyPart> EquppedParts;

	TArray<class UWeaponData*> AvailableWeapons;

	UWeaponData* EquippedWeapon;

protected:
	virtual void BeginPlay() override;

	void RefreshPawnAppearance();

public:

	TArray<FBodyPart> GetHeads();
	TArray<FBodyPart> GetBodies();
	TArray<FBodyPart> GetRightArms();
	TArray<FBodyPart> GetLeftArms();
	TArray<FBodyPart> GetLegs();

	void EquipBodyPart(FBodyPart& InPart);
};
