// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAnimInstance.h"

UZombieAnimInstance::UZombieAnimInstance(const FObjectInitializer &ObjInitializer)
{

}

void UZombieAnimInstance::StartAttack()
{
	if (AttackAnimations.Num() > 0)
	{
		int RandomAnim = FMath::RandRange(0, AttackAnimations.Num() - 1);
		Montage_Play(AttackAnimations[RandomAnim]);
	}
}
