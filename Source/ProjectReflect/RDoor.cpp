// Fill out your copyright notice in the Description page of Project Settings.


#include "RDoor.h"

#include "Components/BoxComponent.h"
#include "Components/RMovingPlatformComponent.h"

// Sets default values
ARDoor::ARDoor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	MovingPlatformComponent = CreateDefaultSubobject<URMovingPlatformComponent>(TEXT("Moving Platform Component"));
	// MovingPlatformComponent->Relat
	MovingPlatformComponent->SetupAttachment(SceneComponent);
	// SetRootComponent(MovingPlatformComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);
	// SetRootComponent(StaticMeshComponent);
	// MovingPlatformComponent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void ARDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ARDoor::Activate()
{
	MovingPlatformComponent->PlayForward(false);
	return true;
}

bool ARDoor::Deactivate()
{
	MovingPlatformComponent->PlayBackward(false);
	return true;
}

