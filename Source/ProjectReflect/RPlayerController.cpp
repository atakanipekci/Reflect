// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerController.h"

#include "Character/RPlayerCharacter.h"


void ARPlayerController::ShowTrajectory(bool show)
{
	if(auto Char = Cast<ARPlayerCharacter>(GetCharacter()))
	{
		Char->ShowTrajectory(show);
	}
}

void ARPlayerController::Shoot()
{
	if(auto Char = Cast<ARPlayerCharacter>(GetCharacter()))
	{
		Char->DebugShoot();
	}
}
