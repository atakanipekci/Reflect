// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RActivatablesLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API URActivatablesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static bool ActivateAllComponents(AActor* Actor, bool bDeactivate = false);
};
