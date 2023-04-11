// Fill out your copyright notice in the Description page of Project Settings.


#include "RSingleUseButton.h"

bool ARSingleUseButton::Activate()
{
	if(bIsActivated == false)
	{
		bIsActivated = true;
		return Super::Activate();
	}

	return false;
}

bool ARSingleUseButton::Deactivate()
{
	return false;
}
