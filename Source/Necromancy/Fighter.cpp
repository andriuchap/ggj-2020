// Fill out your copyright notice in the Description page of Project Settings.


#include "Fighter.h"
#include "Components/SkeletalMeshComponent.h"
#include "BodyPartMeshComponent.h"
#include "BodyPartData.h"
#include "ZombieAnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponData.h"
#include "FighterController.h"

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
	HeadMesh->SetGenerateOverlapEvents(true);

	BodyMesh = CreateDefaultSubobject<UBodyPartMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootComponent);
	BodyMesh->Slot = EBodyPartSlot::BPS_Body;
	BodyMesh->SetMasterPoseComponent(HeadMesh);
	BodyMesh->SetCanEverAffectNavigation(false);
	BodyMesh->SetCollisionProfileName(CollisionName);
	BodyMesh->SetGenerateOverlapEvents(true);

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
	BodyParts.Add(LeftArmMesh);
	BodyParts.Add(RightArmMesh);
	BodyParts.Add(BodyMesh);
	BodyParts.Add(LegsMesh);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetGenerateOverlapEvents(false);
	WeaponMesh->SetVisibility(false);

	Health = 0;
}

// Called when the game starts or when spawned
void AFighter::BeginPlay()
{
	Super::BeginPlay();

	WeaponMesh->AttachToComponent(RightArmMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Item_R"));

	ResetParts();
	EquipWeapon(WeaponData);

	WeaponMesh->OnComponentBeginOverlap.AddDynamic(this, &AFighter::WeaponBeginOverlap);

	Health = GetMaxHealth();
}

void AFighter::WeaponBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != this)
	{
		AFighter* OtherFighter = Cast<AFighter>(OtherActor);
		if (OtherFighter)
		{
			DealDamage(OtherFighter);
		}
	}
}

// Called every frame
void AFighter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFighter::ResetParts()
{
	for (int i = 0; i < BodyParts.Num(); i++)
	{
		BodyParts[i]->ResetPart();
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
		Sum += BodyParts[i]->GetBodyPartData()->Constitution;
	}
	UE_LOG(LogTemp, Warning, TEXT("CON: %d"), Sum);
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

float AFighter::GetMaxHealth()
{
	UE_LOG(LogTemp, Warning, TEXT("Max HP: %f"), GetTotalConstitution() * 20.0F);
	return GetTotalConstitution() * 20.0F;
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
	if (InNewEnable && RightArmMesh->BodyPartHealth > 0.0F)
	{
		WeaponMesh->SetGenerateOverlapEvents(true);
	}
	else
	{
		WeaponMesh->SetGenerateOverlapEvents(false);
	}
}

void AFighter::DealDamage(AFighter * OtherFighter)
{
	float BaseDamage = 0.0;
	if (RightArmMesh->BodyPartHealth > 0.0F)
	{
		BaseDamage = WeaponData->BaseDamage;
	}
	float StrengthBonus = GetTotalStrength();
	float Fluctuation = FMath::FRandRange(-5.0F, 5.0F);
	float TotalDamage = FMath::Clamp(BaseDamage + StrengthBonus + Fluctuation, 1.0F, FLT_MAX);
	EDamageResult DamageResult = OtherFighter->ReceiveDamage(TotalDamage);
	if (DamageResult == EDamageResult::DR_LethalDamage)
	{
		AFighterController* FighterController = Cast<AFighterController>(GetController());
		if (FighterController)
		{
			FighterController->NotifyOpponentDied();
		}
	}
}

EDamageResult AFighter::ReceiveDamage(float InAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Health: %f Damage: %f"), Health, InAmount);
	Health -= InAmount;
	ReceiveDamageToRandomPart(InAmount);
	if (Health <= 0.0F)
	{
		Destroy();
		return EDamageResult::DR_LethalDamage;
	}
	return EDamageResult::DR_DamageDealt;
}

void AFighter::ReceiveDamageToRandomPart(float InAmount)
{
	TArray<UBodyPartMeshComponent*> PendingParts;
	for (int i = 0; i < 3; i++)
	{
		if (BodyParts[i]->BodyPartHealth > 0.0F)
		{
			PendingParts.Add(BodyParts[i]);
		}
	}
	if (PendingParts.Num() > 0)
	{
		int RandPart = FMath::RandRange(0, PendingParts.Num() - 1);
		float HealthLeft = PendingParts[RandPart]->ReceiveDamage(InAmount);
		if (HealthLeft <= 0.0F)
		{
			PendingParts[RandPart]->SetVisibility(false);
			if (PendingParts[RandPart] == RightArmMesh)
			{
				WeaponMesh->SetVisibility(false);
			}
		}
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
