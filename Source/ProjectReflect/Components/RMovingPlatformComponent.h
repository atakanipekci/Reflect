// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "ProjectReflect/Activatables/RIActivatable.h"
#include "RMovingPlatformComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTREFLECT_API URMovingPlatformComponent : public USplineComponent, public IRActivatable
{
	GENERATED_BODY()
	URMovingPlatformComponent();

public:

	virtual void BeginPlay() override;
	bool CanMove() const;
	void ProcessMovement(float DeltaTime);
	void UpdateTimer(float DeltaTime);
	bool GetNewDirection(float Alpha, bool CurrentDirection) const;
	void PlayForward(bool ResetPosition);
	void PlayBackward(bool ResetPosition);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool IActivate() override;
	virtual bool IDeactivate() override;

	UPROPERTY(EditAnywhere)
	float LapTime = 3.f;

	UPROPERTY(EditAnywhere)
	bool bFollowRotation = false;
	
	UPROPERTY(EditAnywhere)
	bool bLoop = false;

	UPROPERTY(EditAnywhere)
	bool bPlayAtStart = false;

	UPROPERTY(EditAnywhere)
	UCurveFloat* MoveCurve;

private:
	float Timer = 0.f;
	int LoopCount;
	bool bForward = true;
	bool bActive = false;
	
};
