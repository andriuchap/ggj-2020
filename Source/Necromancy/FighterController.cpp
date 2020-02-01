// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterController.h"
#include "Fighter.h"

AFighterController::AFighterController(const FObjectInitializer &ObjInitializer)
{
	Opponent = nullptr;
	PreviousPathStatus = EPathFollowingStatus::Idle;
}

void AFighterController::MoveTowardOpponent()
{
	if (Opponent)
	{
		EPathFollowingRequestResult::Type MoveResult = MoveToActor(Opponent, 75.0F);
		//UE_LOG(LogTemp, Warning, TEXT("Distance! %f"), DistanceToOpponent);
		if(MoveResult == EPathFollowingRequestResult::RequestSuccessful)
		{
			FighterState = EFighterState::FS_MovingToOpponent;
			SetFocus(Opponent);
		}
		else
		{
			AttackOrReposition();
		}
	}
}

void AFighterController::Reposition()
{
	FVector PawnLoc = GetPawn()->GetActorLocation();
	FVector PawnFwd = GetPawn()->GetActorForwardVector();

	PawnFwd = PawnFwd.RotateAngleAxis(FMath::RandRange(-90.0F, 90.0F), FVector::UpVector);
	PawnFwd *= FMath::RandRange(100.0F, 250.0F) * -1.0F;

	MoveToLocation(PawnLoc + PawnFwd, 10.0F);

	FighterState = EFighterState::FS_Repositioning;
	SetFocus(Opponent);
}

void AFighterController::EvaluateCombat()
{
	if (Opponent)
	{
		float DistanceToOpponent = FVector::Distance(GetPawn()->GetActorLocation(), Opponent->GetActorLocation());

		if (FighterState == EFighterState::FS_Idle)
		{
			// Move towards the opponent
			UE_LOG(LogTemp, Warning, TEXT("Distance! %f"), DistanceToOpponent);
			if (DistanceToOpponent > 75.0F)
			{
				MoveTowardOpponent();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Repositioning!"));
				Reposition();
			}
		}

		UPathFollowingComponent* PathFollowingComp = GetPathFollowingComponent();
		if (PathFollowingComp)
		{
			EPathFollowingStatus::Type PathStatus = PathFollowingComp->GetStatus();

			//UE_LOG(LogTemp, Warning, TEXT("Prev status: %d Curr status: %d"), PreviousPathStatus, PathStatus);

			if (PreviousPathStatus == EPathFollowingStatus::Moving && PathStatus != EPathFollowingStatus::Moving)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Stopped moving!"));
				// Stopped moving!
				if (FighterState == EFighterState::FS_MovingToOpponent)
				{
					// Was moving to opponent
					AttackOrReposition();

				}
				else if (FighterState == EFighterState::FS_Repositioning)
				{
					// Was Repositioning
					if (DistanceToOpponent > 75.0F)
					{
						MoveTowardOpponent();
					}
				}
			}
			PreviousPathStatus = PathStatus;
		}
	}
}

void AFighterController::AttackOrReposition()
{
	float ChanceToAttack = FMath::FRand();
	if (ChanceToAttack > 0.5F)
	{
		Attack();
	}
	else
	{
		Reposition();
	}
}

void AFighterController::Attack()
{
	// Play animation
	AFighter* Fighter = Cast<AFighter>(GetPawn());
	if (Fighter)
	{
		Fighter->Attack();
		SetFocus(Opponent);
		FighterState = EFighterState::FS_Striking;
	}
}

void AFighterController::AttackFinished()
{
	FighterState = EFighterState::FS_Idle;
	UE_LOG(LogTemp, Warning, TEXT("AttackFinished!"));
}

void AFighterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	EvaluateCombat();
}

void AFighterController::SetOpponent(AFighter * InOpponent)
{
	Opponent = InOpponent;
	SetFocus(Opponent);
}

AFighter * AFighterController::GetOpponent()
{
	return Opponent;
}

EFighterState AFighterController::GetFighterState()
{
	return FighterState;
}
