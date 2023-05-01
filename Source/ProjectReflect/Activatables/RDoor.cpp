// Fill out your copyright notice in the Description page of Project Settings.


#include "RDoor.h"

#include "ProjectReflect/Components/RMovingPlatformComponent.h"
#include "ProjectReflect/Utility/RActivatablesLibrary.h"

// Sets default values
ARDoor::ARDoor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	MovingPlatformComponent = CreateDefaultSubobject<URMovingPlatformComponent>(TEXT("Moving Platform Component"));
	MovingPlatformComponent->SetupAttachment(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
}

// Called when the game starts or when spawned
void ARDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ARDoor::IActivate()
{
	URActivatablesLibrary::ActivateAllComponents(this);
	return true;
}

bool ARDoor::IDeactivate()
{
	URActivatablesLibrary::ActivateAllComponents(this, true);
	return true;
}

