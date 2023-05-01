// Fill out your copyright notice in the Description page of Project Settings.

#include "RProjectileReflector.h"
#include "ProjectReflect/Components/ProjectileInteractor/RProjectileInteractorComponent.h"
#include "ProjectReflect/Utility/RActivatablesLibrary.h"


ARProjectileReflector::ARProjectileReflector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
	
	ProjectileInteractionComponent = CreateDefaultSubobject<URProjectileInteractorComponent>(TEXT("Projectile Interactor"));
	ProjectileInteractionComponent->OnProjectileHitDelegate.AddDynamic(this, &ARProjectileReflector::OnProjectileHit);
	ProjectileInteractionComponent->bEnableBounce = true;
}

void ARProjectileReflector::OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit)
{
}

bool ARProjectileReflector::IActivate()
{
	URActivatablesLibrary::ActivateAllComponents(this);
	return true;
}

bool ARProjectileReflector::IDeactivate()
{
	URActivatablesLibrary::ActivateAllComponents(this, true);
	return true;
}

