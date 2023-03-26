// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileButton.h"

#include "ProjectReflect/Components/ProjectileInteractor/RProjectileInteractorComponent.h"

// Sets default values
ARProjectileButton::ARProjectileButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileInteractionComponent = CreateDefaultSubobject<URProjectileInteractorComponent>(TEXT("Projectile Interactor"));
	ProjectileInteractionComponent->OnProjectileHitDelegate.AddDynamic(this, &ARProjectileButton::OnProjectileHit);
}

// Called when the game starts or when spawned
void ARProjectileButton::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARProjectileButton::OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit)
{
	Activate();
}

// Called every frame
void ARProjectileButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARProjectileButton::Activate()
{
	bool bFlag = false;
	for (auto Actor : ActorsToActivate)
	{
		IRActivatable* Interactable = Cast<IRActivatable>(Actor);
		if(Interactable)
		{
			Interactable->Activate();
			bFlag = true;
		}
	}

	return bFlag;
}

