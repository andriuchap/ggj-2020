// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPartMeshComponent.h"
#include "BodyPartData.h"

UBodyPartMeshComponent::UBodyPartMeshComponent(const FObjectInitializer &ObjInitializer)
{
	Data = nullptr;
	Slot = EBodyPartSlot::BPS_Body;

	BodyPartHealth = 0.0F;
}

UBodyPartData * UBodyPartMeshComponent::GetBodyPartData()
{
	return Data;
}

void UBodyPartMeshComponent::RefreshMesh()
{
	if (Data)
	{
		SetSkeletalMesh(Data->Mesh);
		SetMaterial(0, Data->Material);
	}
}