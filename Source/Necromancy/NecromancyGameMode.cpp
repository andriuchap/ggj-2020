// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NecromancyGameMode.h"
#include "NecromancyHUD.h"
#include "NecromancyCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANecromancyGameMode::ANecromancyGameMode(const FObjectInitializer &ObjInitializer)
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ANecromancyHUD::StaticClass();
}
