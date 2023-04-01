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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FColor> LevelColors;

	const FColor& GetLevelColor(int Level) const
	{
		if(LevelColors.Num() == 0 || Level < 0)
		{
			return FColor::White;
		}
		
		Level = FMath::Min(Level, LevelColors.Num()-1);
		return LevelColors[Level];
	}
};
