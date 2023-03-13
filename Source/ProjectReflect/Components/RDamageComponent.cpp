// Fill out your copyright notice in the Description page of Project Settings.


#include "RDamageComponent.h"

#include "Engine/DamageEvents.h"
#include "ProjectReflect/Data/RDamageData.h"

// Sets default values for this component's properties
URDamageComponent::URDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float URDamageComponent::DealDamage(AActor* TargetActor, const FHitResult& HitResult) const
{
	if(TargetActor)
	{
		const FPointDamageEvent PointDamage(CurrentDamage,HitResult,FVector::ZeroVector, UDamageType::StaticClass());
		return TargetActor->TakeDamage(CurrentDamage, PointDamage, nullptr, GetOwner());
	}
	
	return 0.f;
}


// Called when the game starts
void URDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	if(DamageData)
	{
		CurrentDamage = DamageData->Damage;
	}
}


// Called every frame
void URDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

