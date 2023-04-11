// Fill out your copyright notice in the Description page of Project Settings.


#include "RTimedButton.h"

bool ARTimedButton::Activate()
{
	Timer = DeactivationTime;
	return Super::Activate();
}

bool ARTimedButton::Deactivate()
{
	return Super::Deactivate();
}

void ARTimedButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Timer > 0.f)
	{
		Timer -= DeltaSeconds;
		if(Timer <= 0.f)
		{
			Deactivate();
		}
	}
}
