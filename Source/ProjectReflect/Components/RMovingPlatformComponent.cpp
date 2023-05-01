// Fill out your copyright notice in the Description page of Project Settings.


#include "RMovingPlatformComponent.h"

URMovingPlatformComponent::URMovingPlatformComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void URMovingPlatformComponent::BeginPlay()
{
	Super::BeginPlay();
	DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	bActive = bPlayAtStart;
}

bool URMovingPlatformComponent::CanMove() const
{
	return bActive && (bLoop || !bLoop && LoopCount < 1);
}

void URMovingPlatformComponent::ProcessMovement(float DeltaTime)
{
	if(!CanMove())
	{
		//If completed one loop return
		return;
	}
	
	const float Alpha = Timer/LapTime;
	const float DistanceAlpha = FMath::Lerp(0.f, GetSplineLength(), Alpha);

	GetOwner()->SetActorLocation(GetLocationAtDistanceAlongSpline(DistanceAlpha, ESplineCoordinateSpace::World));

	if(bFollowRotation)
	{
		GetOwner()->SetActorRotation(GetRotationAtDistanceAlongSpline(DistanceAlpha, ESplineCoordinateSpace::World));
	}

	const auto NewDirection = GetNewDirection(Alpha, bForward);
	if(NewDirection != bForward)
	{
		LoopCount++;
		bForward = NewDirection;
	}
	
	UpdateTimer(DeltaTime);
}

void URMovingPlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ProcessMovement(DeltaTime);
}

bool URMovingPlatformComponent::IActivate()
{
	PlayForward(false);
	return true;
}

bool URMovingPlatformComponent::IDeactivate()
{
	PlayBackward(false);
	return true;
}

void URMovingPlatformComponent::UpdateTimer(float DeltaTime)
{
	if(bForward)
	{
		Timer = FMath::Min(Timer+DeltaTime, LapTime);
	}
	else
	{
		Timer = FMath::Max(0.f, Timer-DeltaTime);
	}
}

bool URMovingPlatformComponent::GetNewDirection(const float Alpha, const bool CurrentDirection) const
{
	if(FMath::IsNearlyEqual(Alpha, 1.f))
	{
		return false;
	}
	if(FMath::IsNearlyEqual(Alpha, 0.f))
	{
		return true;
	}

	return CurrentDirection;
}

void URMovingPlatformComponent::PlayForward(const bool ResetPosition)
{
	bActive = true;
	bForward = true;
	LoopCount = 0;
	if(ResetPosition)
	{
		Timer = 0;
	}
}

void URMovingPlatformComponent::PlayBackward(const bool ResetPosition)
{
	bActive = true;
	bForward = false;
	LoopCount = 0;
	if(ResetPosition)
	{
		Timer = LapTime;
	}
}
