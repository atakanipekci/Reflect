// Fill out your copyright notice in the Description page of Project Settings.


#include "RTimeManipulatorComponent.h"

#include "ProjectReflect/TimeModify/RTimeManager.h"

// Sets default values for this component's properties
URTimeManipulatorComponent::URTimeManipulatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URTimeManipulatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URTimeManipulatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URTimeManipulatorComponent::ModifyTimeForSeconds(float Modifier, float Seconds)
{
	if(!GetWorld() || GetWorld()->GetTimerManager().IsTimerActive(TimerHandle_TimeModify))
	{
		return;
	}
	
	RTimeManager::ModifyTime(GetWorld(), Modifier);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_TimeModify, this, &URTimeManipulatorComponent::ResetTimeModifier, Seconds, false);
}

void URTimeManipulatorComponent::ResetTimeModifier()
{
	RTimeManager::ModifyTime(GetWorld(), 1.f, true);
}

