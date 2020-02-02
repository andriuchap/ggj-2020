// Fill out your copyright notice in the Description page of Project Settings.


#include "NecromancyTypes.h"
#include "BodyPartData.h"

FBodyPart::FBodyPart(UBodyPartData * InData) : Data(InData), Health(InData->BodyPartHealth)
{
}
