// Fill out your copyright notice in the Description page of Project Settings.


#include "RLevelComponent.h"

#include "ProjectReflect/Utility/RProjectileLevelLibrary.h"

// Sets default values for this component's properties
URLevelComponent::URLevelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URLevelComponent::BeginPlay()
{
	Super::BeginPlay();

	URProjectileLevelLibrary::SetActorColorByLevel(GetOwner(), Level);
	OnLevelUp.Broadcast(Level, Level);
}


// Called every frame
void URLevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool URLevelComponent::LevelUp()
{
	if(Level < MaxLevel)
	{
		Level++;
		URProjectileLevelLibrary::SetActorColorByLevel(GetOwner(), Level);
		OnLevelUp.Broadcast(Level-1, Level);
		return true;
	}

	return false;
}

