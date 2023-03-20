// Fill out your copyright notice in the Description page of Project Settings.


#include "RPlayerController.h"

#include "Character/RPlayerCharacter.h"


void ARPlayerController::HideTrajectory()
{
	if(auto Char = Cast<ARPlayerCharacter>(GetCharacter()))
	{
		Char->HideTrajectory();
	}
}

void ARPlayerController::ShowTrajectory()
{
	if(auto Char = Cast<ARPlayerCharacter>(GetCharacter()))
	{
		Char->ShowTrajectory();
	}
}