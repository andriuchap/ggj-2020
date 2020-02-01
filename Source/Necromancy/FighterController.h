// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FighterController.generated.h"

UENUM()
enum class EFighterState : uint8
{
	FS_Idle,
	FS_MovingToOpponent,
	FS_Striking,
	FS_Repositioning,
	FS_Blocking
};

UCLASS()
class NECROMANCY_API AFighterController : public AAIController
{
	GENERATED_BODY()
public:
	AFighterController(const FObjectInitializer &ObjInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "Fighter")
	class AFighter* Opponent;

private:
	EFighterState FighterState;
	EPathFollowingStatus::Type PreviousPathStatus;

protected:

	void MoveTowardOpponent();
	void Reposition();

	void EvaluateCombat();

	void Strike();

public:

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Fighter")
	void SetOpponent(AFighter* InOpponent);
	AFighter* GetOpponent();

	EFighterState GetFighterState();
};
