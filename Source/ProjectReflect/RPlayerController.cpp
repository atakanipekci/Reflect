// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerController.h"

#include "Character/RPlayerCharacter.h"


void ARPlayerController::ShowTrajectory(bool Show)
{
	if(auto Char = Cast<ARPlayerCharacter>(GetCharacter()))
	{
		Char->ShowTrajectory(Show);
	}
}

void ARPlayerController::Shoot()
{
	if(auto Char = Cast<ARPlayerCharacter>(GetCharacter()))
	{
		Char->DebugShoot();
	}
}
