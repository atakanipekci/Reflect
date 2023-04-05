// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "RMovingPlatformComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTREFLECT_API URMovingPlatformComponent : public USplineComponent
{
	GENERATED_BODY()
	URMovingPlatformComponent();

public:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float LapTime = 3.f;

	UPROPERTY(EditAnywhere)
	bool bFollowRotation = false;
	
	UPROPERTY(EditAnywhere)
	UCurveFloat* MoveCurve;

private:
	float Timer = 0.f;
	bool bForward = true;
};
