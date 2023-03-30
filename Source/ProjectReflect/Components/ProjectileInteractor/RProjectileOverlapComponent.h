// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RProjectileInteractorComponent.h"
#include "Components/BoxComponent.h"
#include "RProjectileOverlapComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTREFLECT_API URProjectileOverlapComponent : public URProjectileInteractorComponent
{
	GENERATED_BODY()
public:
	URProjectileOverlapComponent();

	UFUNCTION()
	void OnProjectileOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
};
