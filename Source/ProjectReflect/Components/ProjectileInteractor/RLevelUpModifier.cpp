// Fill out your copyright notice in the Description page of Project Settings.


#include "RLevelUpModifier.h"

#include "ProjectReflect/Components/RLevelComponent.h"
#include "ProjectReflect/Projectile/RProjectile.h"

void URLevelUpModifier::ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit)
{
	Super::ApplyBehavior(Projectile, Hit);

	URLevelComponent* LevelComponent = Cast<URLevelComponent>(Projectile->GetComponentByClass(URLevelComponent::StaticClass()));
	LevelComponent->LevelUp();
}
