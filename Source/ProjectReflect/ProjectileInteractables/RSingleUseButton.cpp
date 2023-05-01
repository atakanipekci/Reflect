// Fill out your copyright notice in the Description page of Project Settings.


#include "RSingleUseButton.h"

bool ARSingleUseButton::IActivate()
{
	if(bIsActivated == false)
	{
		bIsActivated = true;
		return Super::IActivate();
	}

	return false;
}

bool ARSingleUseButton::IDeactivate()
{
	return false;
}
