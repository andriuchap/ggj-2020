// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ZombieAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NECROMANCY_API UZombieAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UZombieAnimInstance(const FObjectInitializer &ObjInitializer);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Zombie")
	TArray<class UAnimMontage*> AttackAnimations;

public:
	void StartAttack();
};
