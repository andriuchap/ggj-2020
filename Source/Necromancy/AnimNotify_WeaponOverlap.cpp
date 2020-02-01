// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_WeaponOverlap.h"
#include "Components/SkeletalMeshComponent.h"
#include "Fighter.h"

UAnimNotify_WeaponOverlap::UAnimNotify_WeaponOverlap(const FObjectInitializer &ObjInitializer)
{
	bEnableWeaponOverlap = true;
}

FString UAnimNotify_WeaponOverlap::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_WeaponOverlap::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AFighter* Fighter = Cast<AFighter>(MeshComp->GetOwner());
	if (Fighter)
	{
		Fighter->SetEnableWeaponOverlap(bEnableWeaponOverlap);
	}
}
