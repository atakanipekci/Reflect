// Fill out your copyright notice in the Description page of Project Settings.


#include "RLevelUpModifier.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "ProjectReflect/Utility/RProjectileLevelLibrary.h"

void URLevelUpModifier::ApplyBehavior(ARProjectile* Projectile, const FHitResult& Hit)
{
	Super::ApplyBehavior(Projectile, Hit);

	URProjectileLevelLibrary::TryLevelUpActor(Projectile);
}
