// Fill out your copyright notice in the Description page of Project Settings.


#include "RSwitchButton.h"

bool ARSwitchButton::Activate()
{
	if(bIsActivated)
	{
		bIsActivated = false;
		return Super::Deactivate();
	}
	else
	{
		bIsActivated = true;
		return Super::Activate();
	}
}

bool ARSwitchButton::Deactivate()
{
	return false;
}
