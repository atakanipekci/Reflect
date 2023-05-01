// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectReflect/Activatables/RIActivatable.h"
#include "RRotatingPlatformComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URRotatingPlatformComponent : public UActorComponent, public IRActivatable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URRotatingPlatformComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	bool CanMove() const;
	void UpdateTimer(float DeltaTime);
	bool GetNewDirection(float Alpha, bool CurrentDirection) const;
	void PlayForward(bool ResetPosition);
	void PlayBackward(bool ResetPosition);

	virtual bool IActivate() override;
	virtual bool IDeactivate() override;

	UPROPERTY(EditAnywhere)
	FRotator TargetRotation;
	
	UPROPERTY(EditAnywhere)
	float LapTime = 3.f;
	
	UPROPERTY(EditAnywhere)
	bool bLoop = false;

	UPROPERTY(EditAnywhere)
	bool bPlayAtStart = false;

	//Whether the target rotation is absolute world rotation or it should be used as relative rotation by adding it to the default rotation
	UPROPERTY(EditAnywhere)
	bool bAdditive = false;

protected:
	UPROPERTY()
	FRotator DefaultRotation;
	
	float Timer = 0.f;
	int LoopCount;
	bool bForward = true;
	bool bActive = false;
};
