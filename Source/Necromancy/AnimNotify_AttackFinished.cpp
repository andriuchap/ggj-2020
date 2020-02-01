// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_AttackFinished.h"
#include "Components/SkeletalMeshComponent.h"
#include "Fighter.h"
#include "FighterController.h"

UAnimNotify_AttackFinished::UAnimNotify_AttackFinished(const FObjectInitializer &ObjInitializer)
{

}

FString UAnimNotify_AttackFinished::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_AttackFinished::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AFighter* Fighter = Cast<AFighter>(MeshComp->GetOwner());
	if (Fighter)
	{
		AFighterController* Controller = Cast<AFighterController>(Fighter->GetController());
		if (Controller)
		{
			Controller->AttackFinished();
		}
	}
}
