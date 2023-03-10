// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RDamageData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTREFLECT_API URDamageData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float Damage;
	
};
