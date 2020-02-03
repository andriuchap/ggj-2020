// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NecromancyTypes.h"
#include "NecromancerPawn.generated.h"

UCLASS(Blueprintable)
class NECROMANCY_API ANecromancerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANecromancerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Necromancer")
		void RefreshZombieAppearance(EBodyPartSlot InSlot);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Necromancer")
	FBodyPart GetBodyPart(EBodyPartSlot InSlot);

};
