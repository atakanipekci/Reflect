// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RITimeModifiable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URTimeModifiable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTREFLECT_API IRTimeModifiable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual float GetTimeModifierMultiplier() const { return 1.f;}
};

