// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter.h"
#include "Components/SkeletalMeshComponent.h"
#include "BodyPartMeshComponent.h"
#include "BodyPartData.h"

// Sets default values
AFighter::AFighter(const FObjectInitializer &ObjInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	FName CollisionName = FName("CharacterMesh");

	HeadMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(RootComponent);
	HeadMesh->Slot = EBodyPartSlot::BPS_Head;
	HeadMesh->SetCanEverAffectNavigation(false);
	HeadMesh->SetCollisionProfileName(CollisionName);

	BodyMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->Slot = EBodyPartSlot::BPS_Body;
	BodyMesh->SetMasterPoseComponent(HeadMesh);
	BodyMesh->SetCanEverAffectNavigation(false);
	BodyMesh->SetCollisionProfileName(CollisionName);

	LeftArmMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("LeftArmMesh"));
	LeftArmMesh->SetupAttachment(RootComponent);
	LeftArmMesh->Slot = EBodyPartSlot::BPS_LArm;
	LeftArmMesh->SetMasterPoseComponent(HeadMesh);
	LeftArmMesh->SetCanEverAffectNavigation(false);
	LeftArmMesh->SetCollisionProfileName(CollisionName);

	RightArmMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(RootComponent);
	RightArmMesh->Slot = EBodyPartSlot::BPS_RArm;
	RightArmMesh->SetMasterPoseComponent(HeadMesh);
	RightArmMesh->SetCanEverAffectNavigation(false);
	RightArmMesh->SetCollisionProfileName(CollisionName);

	LegsMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("LegsMesh "));
	LegsMesh->SetupAttachment(RootComponent);
	LegsMesh->Slot = EBodyPartSlot::BPS_Legs;
	LegsMesh->SetMasterPoseComponent(HeadMesh);
	LegsMesh->SetCanEverAffectNavigation(false);
	LegsMesh->SetCollisionProfileName(CollisionName);

	BodyParts.Add(HeadMesh);
	BodyParts.Add(BodyMesh);
	BodyParts.Add(LeftArmMesh);
	BodyParts.Add(RightArmMesh);
	BodyParts.Add(LegsMesh);
}

// Called when the game starts or when spawned
void AFighter::BeginPlay()
{
	Super::BeginPlay();
	RefreshAppearance();
}

// Called every frame
void AFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFighter::RefreshAppearance()
{
	for (int i = 0; i < BodyParts.Num(); i++)
	{
		BodyParts[i]->RefreshMesh();
	}
}

int AFighter::GetTotalStrength()
{
	int Sum = 0;
	for (int i = 0; i < BodyParts.Num(); i++)
	{
		if (BodyParts[i]->BodyPartHealth > 0.0F)
		{
			Sum += BodyParts[i]->GetBodyPartData()->Strength;
		}
	}
	return Sum;
}

int AFighter::GetTotalConstitution()
{
	int Sum = 0;
	for (int i = 0; i < BodyParts.Num(); i++)
	{
		Sum += BodyParts[i]->GetBodyPartData()->Strength;
	}
	return Sum;
}

int AFighter::GetTotalDexterity()
{
	int Sum = 0;
	for (int i = 0; i < BodyParts.Num(); i++)
	{
		if (BodyParts[i]->BodyPartHealth > 0.0F)
		{
			Sum += BodyParts[i]->GetBodyPartData()->Dexterity;
		}
	}
	return Sum;
}

int AFighter::GetTotalIntelligence()
{
	int Sum = 0;
	for (int i = 0; i < BodyParts.Num(); i++)
	{
		if (BodyParts[i]->BodyPartHealth > 0.0F)
		{
			Sum += BodyParts[i]->GetBodyPartData()->Intelligence;
		}
	}
	return Sum;
}
