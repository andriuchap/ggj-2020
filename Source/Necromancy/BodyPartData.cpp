// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPartData.h"

UBodyPartData::UBodyPartData(const FObjectInitializer &ObjInitializer)
{
	Slot = EBodyPartSlot::BPS_Body;

	Name = FText();

	Strength = 0;
	Dexterity = 0;
	Constitution = 0;
	Intelligence = 0;

	BodyPartHealth = 50.0F;

	Mesh = nullptr;
	Material = nullptr;
}