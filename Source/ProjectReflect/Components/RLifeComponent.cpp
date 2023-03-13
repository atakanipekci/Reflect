// Fill out your copyright notice in the Description page of Project Settings.


#include "RLifeComponent.h"

#include "Engine/DamageEvents.h"

// Sets default values for this component's properties
URLifeComponent::URLifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	CurrentHealth = MaxHealth;
}

float URLifeComponent::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(DamageAmount < DamageThreshold)
	{
		return 0.f;
	}
	
	float OldHealth = CurrentHealth;
	CurrentHealth = FMath::Max(0.f, CurrentHealth-DamageAmount);

	bool bDied = false;
	FHitResult HitResult;
	FVector HitImpulse;
	DamageEvent.GetBestHitInfo(GetOwner(),EventInstigator,HitResult,HitImpulse);

	if(FMath::IsNearlyEqual(0.f, CurrentHealth))
	{
		bDied = true;
		HealthReachedZero.Broadcast();
	}
	
	TookDamage.Broadcast(HitResult, bDied);

	return OldHealth-CurrentHealth;
}


// Called when the game starts
void URLifeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URLifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

