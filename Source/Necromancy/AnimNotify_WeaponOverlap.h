// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_WeaponOverlap.generated.h"

/**
 * 
 */
UCLASS()
class NECROMANCY_API UAnimNotify_WeaponOverlap : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_WeaponOverlap(const FObjectInitializer &ObjInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bEnableWeaponOverlap;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FString GetNotifyName_Implementation() const override;
};
