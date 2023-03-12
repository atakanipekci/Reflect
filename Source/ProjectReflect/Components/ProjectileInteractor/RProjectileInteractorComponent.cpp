// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileInteractorComponent.h"

#include "ProjectReflect/Components/ProjectileInteractor/RProjectileBehaviorModifier.h"
#include "ProjectReflect/Projectile/RProjectile.h"


// Sets default values for this component's properties
URProjectileInteractorComponent::URProjectileInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void URProjectileInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	BehaviorModifiers.Empty();
	if(const auto Owner = GetOwner())
	{
		auto AllComponents = Owner->GetComponents();
		for (const auto Component : AllComponents)
		{
			if(auto ModifierComponent = Cast<URProjectileBehaviorModifier>(Component))
			{
				UE_LOG(LogStats, Log, TEXT("ProjectileInteractor Constructor addCOmponent -> %s"), *ModifierComponent->GetName());
				BehaviorModifiers.Add(ModifierComponent);
			}
		} 
	}
	
}


// Called every frame
void URProjectileInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URProjectileInteractorComponent::OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit)
{
	UE_LOG(LogStats, Log, TEXT("ProjectileInteractor OnHit -> %s"), *Projectile->GetName());
	OnProjectileHitDelegate.Broadcast(Projectile, Hit);
	for (const auto Modifier : BehaviorModifiers)
	{
		if(Modifier)
		{
			Modifier->ApplyBehavior(Projectile, Hit);
		}
	}
}

