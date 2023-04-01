// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLevelComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelUp, int, OldLevel, int, NewLevel);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URLevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URLevelComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool LevelUp();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnLevelUp OnLevelUp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 0))
	int Level = 0;
protected:


	
		
};
