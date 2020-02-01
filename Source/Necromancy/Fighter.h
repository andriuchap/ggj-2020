// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
		class UBodyPartMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		class UBodyPartMeshComponent* LeftArmMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		class UBodyPartMeshComponent* RightArmMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Body parts")
		class UBodyPartMeshComponent* LegsMesh;

	TArray<UBodyPartMeshComponent*> BodyParts;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RefreshAppearance();

	int GetTotalStrength();
	int GetTotalConstitution();
	int GetTotalDexterity();
	int GetTotalIntelligence();

	void Attack();
};
