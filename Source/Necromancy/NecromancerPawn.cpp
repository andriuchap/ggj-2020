// Fill out your copyright notice in the Description page of Project Settings.


#include "NecromancerPawn.h"
#include "NecromancerController.h"

// Sets default values
ANecromancerPawn::ANecromancerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ANecromancerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANecromancerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANecromancerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FBodyPart ANecromancerPawn::GetBodyPart(EBodyPartSlot InSlot)
{
	ANecromancerController* NecroController = Cast<ANecromancerController>(GetController());
	if (NecroController)
	{
		return NecroController->EquppedParts[InSlot];
	}
	return FBodyPart();
}

