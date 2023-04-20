// Fill out your copyright notice in the Description page of Project Settings.


#include "RRotatingPlatformComponent.h"

// Sets default values for this component's properties
URRotatingPlatformComponent::URRotatingPlatformComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	if(GetOwner())
	{
		DefaultRotation = GetOwner()->GetActorRotation();
	}
}


// Called when the game starts
void URRotatingPlatformComponent::BeginPlay()
{
	Super::BeginPlay();
	bActive = bPlayAtStart;
}


// Called every frame
void URRotatingPlatformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!GetOwner() || !CanMove())
	{
		return;
	}

	float Alpha = Timer/LapTime;

	GetOwner()->SetActorRotation(FMath::Lerp(DefaultRotation, TargetRotation, Alpha));

	UpdateTimer(DeltaTime);

	const auto NewDirection = GetNewDirection(Alpha, bForward);
	if(NewDirection != bForward)
	{
		LoopCount++;
		bForward = NewDirection;
	}
}

bool URRotatingPlatformComponent::CanMove() const
{
	return bActive && (bLoop || !bLoop && LoopCount < 1);
}

void URRotatingPlatformComponent::UpdateTimer(float DeltaTime)
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

bool URRotatingPlatformComponent::GetNewDirection(const float Alpha, const bool CurrentDirection) const
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

void URRotatingPlatformComponent::PlayForward(const bool ResetPosition)
{
	bActive = true;
	bForward = true;
	LoopCount = 0;
	if(ResetPosition)
	{
		Timer = 0;
	}
}

void URRotatingPlatformComponent::PlayBackward(const bool ResetPosition)
{
	bActive = true;
	bForward = false;
	LoopCount = 0;
	if(ResetPosition)
	{
		Timer = LapTime;
	}
}


