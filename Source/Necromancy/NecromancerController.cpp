// Fill out your copyright notice in the Description page of Project Settings.


#include "NecromancerController.h"
#include "BodyPartData.h"
#include "Engine/World.h"
#include "NecromancyGameMode.h"
#include "NecromancerPawn.h"

ANecromancerController::ANecromancerController(const FObjectInitializer &ObjInitializer)
{
	bEnableMouseOverEvents = true;
	bEnableClickEvents = true;

	bShowMouseCursor = true;
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
			for (int i = 0; i < GameMode->StartingBodyParts.Num(); i++)
			{
				FBodyPart BodyPart(GameMode->StartingBodyParts[i]);
				EquipBodyPart(BodyPart);
			}
			EquippedWeapon = GameMode->StartingWeapon;
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
	EquppedParts.Add(InPart.Data->Slot, InPart);
	ANecromancerPawn* NecroPawn = Cast<ANecromancerPawn>(GetPawn());
	if (NecroPawn)
	{
		NecroPawn->RefreshZombieAppearance(InPart);
	}
}
