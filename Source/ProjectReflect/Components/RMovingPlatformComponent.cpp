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
}

void URMovingPlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float Alpha = Timer/LapTime;
	float DistanceAlpha = FMath::Lerp(0.f, GetSplineLength(), Alpha);

	GetOwner()->SetActorLocation(GetLocationAtDistanceAlongSpline(DistanceAlpha, ESplineCoordinateSpace::World));

	if(bFollowRotation)
	{
		GetOwner()->SetActorRotation(GetRotationAtDistanceAlongSpline(DistanceAlpha, ESplineCoordinateSpace::World));
	}

	if(FMath::IsNearlyEqual(Alpha, 1.f))
	{
		bForward = false;
	}
	else if(FMath::IsNearlyEqual(Alpha, 0.f))
	{
		bForward = true;
	}

	if(bForward)
	{
		Timer = FMath::Min(Timer+DeltaTime, LapTime);
	}
	else
	{
		Timer = FMath::Max(0.f, Timer-DeltaTime);
	}
}
