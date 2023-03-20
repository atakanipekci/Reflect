// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(Exec, Category = "Commands")
	void HideTrajectory();

	UFUNCTION(Exec, Category = "Commands")
	void ShowTrajectory();
};
