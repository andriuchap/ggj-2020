// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter.h"
#include "Components/SkeletalMeshComponent.h"
#include "BodyPartMeshComponent.h"
#include "BodyPartData.h"
#include "ZombieAnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponData.h"

// Sets default values
AFighter::AFighter(const FObjectInitializer &ObjInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	FName CollisionName = FName("CharacterMesh");

	BodyMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->Slot = EBodyPartSlot::BPS_Body;
	//BodyMesh->SetMasterPoseComponent(HeadMesh);
	BodyMesh->SetCanEverAffectNavigation(false);
	BodyMesh->SetCollisionProfileName(CollisionName);
	BodyMesh->SetGenerateOverlapEvents(true);

	HeadMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(RootComponent);
	HeadMesh->Slot = EBodyPartSlot::BPS_Head;
	HeadMesh->SetCanEverAffectNavigation(false);
	HeadMesh->SetCollisionProfileName(CollisionName);
	HeadMesh->SetGenerateOverlapEvents(true);

	LeftArmMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("LeftArmMesh"));
	LeftArmMesh->SetupAttachment(RootComponent);
	LeftArmMesh->Slot = EBodyPartSlot::BPS_LArm;
	LeftArmMesh->SetMasterPoseComponent(HeadMesh);
	LeftArmMesh->SetCanEverAffectNavigation(false);
	LeftArmMesh->SetCollisionProfileName(CollisionName);
	LeftArmMesh->SetGenerateOverlapEvents(true);

	RightArmMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("RightArmMesh"));
	RightArmMesh->SetupAttachment(RootComponent);
	RightArmMesh->Slot = EBodyPartSlot::BPS_RArm;
	RightArmMesh->SetMasterPoseComponent(HeadMesh);
	RightArmMesh->SetCanEverAffectNavigation(false);
	RightArmMesh->SetCollisionProfileName(CollisionName);
	RightArmMesh->SetGenerateOverlapEvents(true);

	LegsMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("LegsMesh "));
	LegsMesh->SetupAttachment(RootComponent);
	LegsMesh->Slot = EBodyPartSlot::BPS_Legs;
	LegsMesh->SetMasterPoseComponent(HeadMesh);
	LegsMesh->SetCanEverAffectNavigation(false);
	LegsMesh->SetCollisionProfileName(CollisionName);
	LegsMesh->SetGenerateOverlapEvents(true);

	BodyParts.Add(HeadMesh);
	BodyParts.Add(BodyMesh);
	BodyParts.Add(LeftArmMesh);
	BodyParts.Add(RightArmMesh);
	BodyParts.Add(LegsMesh);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetGenerateOverlapEvents(false);
	WeaponMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void AFighter::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->AttachToComponent(RightArmMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Item_R"));

	RefreshAppearance();
	EquipWeapon(WeaponData);

	WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AFighter::WeaponBeginOverlap);
	WeaponMesh->OnComponentEndOverlap.AddDynamic(this, &AFighter::WeaponEndOverlap);
}

void AFighter::WeaponBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped component %s on Actor %s"), *OtherComp->GetReadableName(), *OtherActor->GetName());
	}
}

void AFighter::WeaponEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ended overlap component %s on Actor %s"), *OtherComp->GetReadableName(), *OtherActor->GetName());
	}
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

void AFighter::Attack()
{
	UZombieAnimInstance* AnimInstance = Cast<UZombieAnimInstance>(HeadMesh->GetAnimInstance());
	if (AnimInstance)
	{
		AnimInstance->StartAttack();
	}
}

void AFighter::SetEnableWeaponOverlap(bool InNewEnable)
{
	if (InNewEnable)
	{
		WeaponMesh->SetGenerateOverlapEvents(true);
	}
	else
	{
		WeaponMesh->SetGenerateOverlapEvents(false);
	}
}

void AFighter::EquipWeapon(UWeaponData * InWeaponData)
{
	if (InWeaponData)
	{
		WeaponData = InWeaponData;
		WeaponMesh->SetStaticMesh(WeaponData->WeaponMesh);
		if (WeaponData->WeaponMaterial)
		{
			WeaponMesh->SetMaterial(0, WeaponData->WeaponMaterial);
		}

		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));
	}
	else
	{
		WeaponMesh->SetVisibility(true);
		WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	}
}
