// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AttackFinished.generated.h"

/**
 * 
 */
UCLASS()
class NECROMANCY_API UAnimNotify_AttackFinished : public UAnimNotify
{
	GENERATED_BODY()
public:
	UAnimNotify_AttackFinished(const FObjectInitializer &ObjInitializer);

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FString GetNotifyName_Implementation() const override;
};
