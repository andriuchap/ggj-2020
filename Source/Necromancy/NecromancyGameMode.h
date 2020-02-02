// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NecromancyGameMode.generated.h"

UCLASS(minimalapi)
class ANecromancyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANecromancyGameMode(const FObjectInitializer &ObjInitializer);

public:

	UPROPERTY(EditAnywhere, Category = "Body Parts")
	TArray<class UBodyPartData*> StartingBodyParts;

	UPROPERTY(EditAnywhere, Category = "Body Parts")
	class UWeaponData* StartingWeapon;

	TArray<class AFighter*> Fighters;
	TArray<FTransform> FighterTransforms;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Necromancy")
	void StartFight(class ANecromancerController* Necro);
};



