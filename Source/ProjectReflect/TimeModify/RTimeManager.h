// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECTREFLECT_API RTimeManager
{
public:
	RTimeManager();
	~RTimeManager();

	static void ModifyTime(UWorld* World, float Modifier, bool bIgnoreCustomMultipliers = false);
};
