// Fill out your copyright notice in the Description page of Project Settings.


#include "RTimedButton.h"

bool ARTimedButton::IActivate()
{
	Timer = DeactivationTime;
	return Super::IActivate();
}

bool ARTimedButton::IDeactivate()
{
	return Super::IDeactivate();
}

void ARTimedButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Timer > 0.f)
	{
		Timer -= DeltaSeconds;
		if(Timer <= 0.f)
		{
			IDeactivate();
		}
	}
}
