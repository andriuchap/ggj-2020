// Fill out your copyright notice in the Description page of Project Settings.


#include "NecromancerController.h"
#include "BodyPartData.h"
#include "Engine/World.h"
#include "NecromancyGameMode.h"
#include "NecromancerPawn.h"
#include "BodyPartMeshComponent.h"
#include "Fighter.h"

ANecromancerController::ANecromancerController(const FObjectInitializer &ObjInitializer)
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	bShowMouseCursor = true;

	RemainingHealth = 0;
}

void ANecromancerController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		ANecromancyGameMode* GameMode = Cast<ANecromancyGameMode>(World->GetAuthGameMode());
		if (GameMode)
		{
			int Constitution = 0;
			for (int i = 0; i < GameMode->StartingBodyParts.Num(); i++)
			{
				FBodyPart BodyPart(GameMode->StartingBodyParts[i]);
				Constitution += BodyPart.Data->Constitution;
				EquipBodyPart(BodyPart);
			}
			EquippedWeapon = GameMode->StartingWeapon;

			RemainingHealth = Constitution * 20.0F;
		}
	}	
}

void ANecromancerController::RefreshPawnAppearance()
{
	ANecromancerPawn* NecroPawn = Cast<ANecromancerPawn>(GetPawn());
	if (NecroPawn)
	{
		//NecroPawn->RefreshZombieAppearance(EquppedParts);
	}
}

TArray<FBodyPart> ANecromancerController::GetHeads()
{
	TArray<FBodyPart> Result;
	for (int i = 0; i < AvailableParts.Num(); i++)
	{
		if (AvailableParts[i].Data->Slot == EBodyPartSlot::BPS_Head)
		{
			Result.Add(AvailableParts[i]);
		}
	}
	return Result;
}

TArray<FBodyPart> ANecromancerController::GetBodies()
{
	TArray<FBodyPart> Result;
	for (int i = 0; i < AvailableParts.Num(); i++)
	{
		if (AvailableParts[i].Data->Slot == EBodyPartSlot::BPS_Body)
		{
			Result.Add(AvailableParts[i]);
		}
	}
	return Result;
}

TArray<FBodyPart> ANecromancerController::GetRightArms()
{
	TArray<FBodyPart> Result;
	for (int i = 0; i < AvailableParts.Num(); i++)
	{
		if (AvailableParts[i].Data->Slot == EBodyPartSlot::BPS_RArm)
		{
			Result.Add(AvailableParts[i]);
		}
	}
	return Result;
}

TArray<FBodyPart> ANecromancerController::GetLeftArms()
{
	TArray<FBodyPart> Result;
	for (int i = 0; i < AvailableParts.Num(); i++)
	{
		if (AvailableParts[i].Data->Slot == EBodyPartSlot::BPS_LArm)
		{
			Result.Add(AvailableParts[i]);
		}
	}
	return Result;
}

TArray<FBodyPart> ANecromancerController::GetLegs()
{
	TArray<FBodyPart> Result;
	for (int i = 0; i < AvailableParts.Num(); i++)
	{
		if (AvailableParts[i].Data->Slot == EBodyPartSlot::BPS_Legs)
		{
			Result.Add(AvailableParts[i]);
		}
	}
	return Result;
}

void ANecromancerController::EquipBodyPart(FBodyPart & InPart)
{
	EquippedParts.Add(InPart.Data->Slot, InPart);
	ANecromancerPawn* NecroPawn = Cast<ANecromancerPawn>(GetPawn());
	if (NecroPawn)
	{
		NecroPawn->RefreshZombieAppearance(InPart.Data->Slot);
	}
}

void ANecromancerController::UnequipBodyPart(FBodyPart & InPart)
{
	EBodyPartSlot Slot = InPart.Data->Slot;
	if (EquippedParts[Slot] == InPart)
	{
		EquippedParts.Remove(Slot);
	}
	AvailableParts.Add(InPart);
	ANecromancerPawn* NecroPawn = Cast<ANecromancerPawn>(GetPawn());
	if (NecroPawn)
	{
		NecroPawn->RefreshZombieAppearance(InPart.Data->Slot);
	}
}

void ANecromancerController::DestroyBodyPart(FBodyPart & InPart)
{
	AvailableParts.Remove(InPart);
}

void ANecromancerController::TransferFighterData(AFighter * Fighter)
{
	RemainingHealth = Fighter->Health;

	EvaluateEquippedPart(EBodyPartSlot::BPS_Head, Fighter->HeadMesh);
	EvaluateEquippedPart(EBodyPartSlot::BPS_Body, Fighter->BodyMesh);
	EvaluateEquippedPart(EBodyPartSlot::BPS_Legs, Fighter->LegsMesh);
	EvaluateEquippedPart(EBodyPartSlot::BPS_LArm, Fighter->LeftArmMesh);
	EvaluateEquippedPart(EBodyPartSlot::BPS_RArm, Fighter->RightArmMesh);
}

void ANecromancerController::EvaluateEquippedPart(EBodyPartSlot Slot, UBodyPartMeshComponent * MeshComp)
{
	if (EquippedParts.Contains(Slot))
	{
		FBodyPart& Part = EquippedParts[Slot];
		Part.Health = MeshComp->BodyPartHealth;
		if (Part.Health <= 0.0F)
		{
			UnequipBodyPart(Part);
			DestroyBodyPart(Part);
		}
	}
}
