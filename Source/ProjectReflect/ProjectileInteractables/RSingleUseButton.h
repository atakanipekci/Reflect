// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileButton.h"
#include "RSingleUseButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARSingleUseButton : public ARProjectileButton
{
	GENERATED_BODY()

public:
	
	virtual bool IActivate() override;
	virtual bool IDeactivate() override;
	
};
