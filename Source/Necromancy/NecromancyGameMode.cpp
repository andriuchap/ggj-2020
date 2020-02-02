// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NecromancyGameMode.h"
#include "NecromancyHUD.h"
#include "NecromancyCharacter.h"
#include "NecromancerController.h"
#include "NecromancerPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Fighter.h"
#include "ObserverPawn.h"
#include "FighterController.h"

ANecromancyGameMode::ANecromancyGameMode(const FObjectInitializer &ObjInitializer)
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = ANecromancerController::StaticClass();
}

void ANecromancyGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<AFighter> Itr(GetWorld()); Itr; ++Itr)
	{
		AFighter* Fighter = *Itr;
		Fighters.Add(Fighter);
		Fighter->OnFighterDied.AddUObject(this, &ANecromancyGameMode::OnFighterDied);
		FighterTransforms.Add(Fighter->GetTransform());
	}
}

void ANecromancyGameMode::StartFight(ANecromancerController* Necro)
{
	for (int i = 0; i < Fighters.Num(); i++)
	{
		Fighters[i]->SetActorTransform(FighterTransforms[i]);
	}
	PlayerFighter = FMath::RandRange(0, 1);

	TArray<EBodyPartSlot> Keys;
	Necro->EquippedParts.GetKeys(Keys);
	for (int i = 0; i < Keys.Num(); i++)
	{
		Fighters[PlayerFighter]->SetPart(Necro->EquippedParts[Keys[i]]);
	}

	for (TActorIterator<AObserverPawn> Itr(GetWorld()); Itr; ++Itr)
	{
		Necro->Possess(*Itr);
	}

	for (int i = 0; i < 2; i++)
	{
		AFighterController* FighterController = Cast<AFighterController>(Fighters[i]->GetController());
		if (FighterController)
		{
			UE_LOG(LogTemp, Warning, TEXT("HECK"));
			FighterController->SetOpponent(Fighters[1 - i]);
		}
	}
}

void ANecromancyGameMode::OnFighterDied(AFighter * Fighter)
{
	/*ANecromancerController* NecroController = nullptr;
	for (TActorIterator<ANecromancerController> Itr(GetWorld()); Itr; ++Itr)
	{
		NecroController = *Itr;
	}
	if (NecroController)
	{
		NecroController->TransferFighterData(Fighters[PlayerFighter]);
		for (TActorIterator<ANecromancerPawn> Itr(GetWorld()); Itr; ++Itr)
		{
			NecroController->Possess(*Itr);
		}
	}*/
}
