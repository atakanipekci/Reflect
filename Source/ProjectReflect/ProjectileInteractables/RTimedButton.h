// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileButton.h"
#include "RTimedButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARTimedButton : public ARProjectileButton
{
	GENERATED_BODY()

public:

	virtual bool Activate() override;
	virtual bool Deactivate() override;

	virtual void Tick(float DeltaSeconds) override;

	const float DeactivationTime = 5.f;
private:

	float Timer = 0.f;
};
