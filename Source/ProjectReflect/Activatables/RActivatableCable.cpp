// Fill out your copyright notice in the Description page of Project Settings.


#include "RActivatableCable.h"

// Sets default values
ARActivatableCable::ARActivatableCable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ARActivatableCable::Activate()
{
	ActivateCable(true);
	bIsActive = true;
	return true;
}

bool ARActivatableCable::Deactivate()
{
	ActivateCable(false);
	bIsActive = false;
	return true;
}

bool ARActivatableCable::TryActivatingAttachedActor()
{
	if(IRActivatable* Activatable = Cast<IRActivatable>(ActivatableActor))
	{
		Activatable->Activate();
		return true;
	}

	return false;
}

// Called when the game starts or when spawned
void ARActivatableCable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARActivatableCable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

