// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RProjectileLevelLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API URProjectileLevelLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static bool TryLevelUpActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static void SetActorColorByLevel(AActor* Actor, int Level);

};
