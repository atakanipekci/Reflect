// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RLevelUpData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTREFLECT_API URLevelUpData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<UMaterialInstance*> MaterialInstancePerLevel; 

	FColor GetLevelColor(int Level) const
	{
		if(const UMaterialInstance* MaterialInstance = GetLevelMaterial(Level))
		{
			FLinearColor Color;
			FHashedMaterialParameterInfo Parameter = FHashedMaterialParameterInfo("DiffuseColor");
			MaterialInstance->GetVectorParameterValue(Parameter, Color);
			return Color.ToFColor(true);
		}
		
		return FColor::White;
	}

	UMaterialInstance* GetLevelMaterial(int Level) const
	{
		if(MaterialInstancePerLevel.Num() == 0 || Level < 0)
		{
			return nullptr;
		}
		
		Level = FMath::Min(Level, MaterialInstancePerLevel.Num()-1);
		return MaterialInstancePerLevel[Level];
	}
};
