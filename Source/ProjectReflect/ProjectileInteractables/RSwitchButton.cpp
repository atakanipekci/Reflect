// Fill out your copyright notice in the Description page of Project Settings.


#include "RSwitchButton.h"

bool ARSwitchButton::IActivate()
{
	if(bIsActivated)
	{
		bIsActivated = false;
		return Super::IDeactivate();
	}
	else
	{
		bIsActivated = true;
		return Super::IActivate();
	}
}

bool ARSwitchButton::IDeactivate()
{
	return false;
}
