// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RCharacter.h"
#include "REnemyCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTREFLECT_API AREnemyCharacter : public ARCharacter
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void FireWeapon();
	
};
