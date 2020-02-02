// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NecromancyTypes.h"
#include "Fighter.generated.h"

UCLASS()
class NECROMANCY_API AFighter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFighter(const FObjectInitializer &ObjInitializer);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		class UBodyPartMeshComponent* HeadMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		UBodyPartMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		UBodyPartMeshComponent* LeftArmMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		UBodyPartMeshComponent* RightArmMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		UBodyPartMeshComponent* LegsMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
		class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	class UWeaponData* WeaponData;

	TArray<UBodyPartMeshComponent*> BodyParts;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	float Health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ResetParts();

	int GetTotalStrength();
	int GetTotalConstitution();
	int GetTotalDexterity();
	int GetTotalIntelligence();

	float GetMaxHealth();

	void Attack();
	void SetEnableWeaponOverlap(bool InNewEnable);
	void DealDamage(AFighter* OtherFighter);
	EDamageResult ReceiveDamage(float InAmount);
	void ReceiveDamageToRandomPart(float InAmount);

	void EquipWeapon(UWeaponData* InWeaponData);

};
