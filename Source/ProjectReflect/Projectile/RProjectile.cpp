// Fill out your copyright notice in the Description page of Project Settings.

#include "RProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjectReflect/Components/RDamageComponent.h"
#include "ProjectReflect/Components/RLevelComponent.h"
#include "ProjectReflect/Components/ProjectileInteractor/RProjectileInteractorComponent.h"
#include "ProjectReflect/Utility/CollisionProfileNames.h"

ARProjectile::ARProjectile() 
{
	InnerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	InnerCollision->InitSphereRadius(25.0f);
	InnerCollision->BodyInstance.SetCollisionProfileName(CollisionProfileNames::Projectile);
	InnerCollision->OnComponentHit.AddDynamic(this, &ARProjectile::OnHit);

	InnerCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	InnerCollision->CanCharacterStepUpOn = ECB_No;
	RootComponent = InnerCollision;

	DamageComponent = CreateDefaultSubobject<URDamageComponent>(TEXT("Damage Component"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = InnerCollision;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &ARProjectile::OnBounce);
	ProjectileMovement->OnProjectileStop.AddDynamic(this, &ARProjectile::OnStop);
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1;
	ProjectileMovement->Friction = 0;

	LevelComponent = CreateDefaultSubobject<URLevelComponent>(TEXT("Level Component"));
	LevelComponent->OnLevelUp.AddDynamic(this, &ARProjectile::OnLevelUp);
}

void ARProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogStats, Log, TEXT("OnProjectile OnHit"));
	if(OtherActor == nullptr)
	{
		UE_LOG(LogStats, Log, TEXT("OnProjectile OnHit-->OtherActor is null"));
	}

	LastHitInteractorComponent = GetInteractorComponentFromActor(OtherActor);
	TryInvokeInteractorComponent(LastHitInteractorComponent, Hit);
	
	OnProjectileHit.Broadcast(OtherActor, Hit);

	if(DamageComponent && OtherActor)
	{
		DamageComponent->DealDamage(OtherActor, Hit);
	}
}

URProjectileInteractorComponent* ARProjectile::GetInteractorComponentFromActor(const AActor* OtherActor) const
{
	if(OtherActor)
	{
		if(const auto InteractorComponent = Cast<URProjectileInteractorComponent>(OtherActor->GetComponentByClass(URProjectileInteractorComponent::StaticClass())))
		{
			return InteractorComponent;
		}
	}

	return nullptr;
}

void ARProjectile::TryInvokeInteractorComponent(URProjectileInteractorComponent* InteractorComponent, const FHitResult& Hit)
{
	if(InteractorComponent)
	{
		InteractorComponent->OnProjectileHit(this, Hit);
	}
	else
	{
		DestroyProjectile();
	}
}


void ARProjectile::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	CurrentBounceCount++;
	UE_LOG(LogStats, Log, TEXT("OnProjectile OnBounce %d"), CurrentBounceCount);
	
	OnProjectileBounce.Broadcast(LastHitInteractorComponent, LastHitActor,ImpactResult, ImpactVelocity);
	
	if(BounceCountToDestroy != 0 && CurrentBounceCount >= BounceCountToDestroy)
	{
		DestroyProjectile();
	}
	
}
void ARProjectile::OnStop(const FHitResult& ImpactResult)
{
	UE_LOG(LogStats, Log, TEXT("OnProjectile OnStop"));
	OnProjectileStop.Broadcast(ImpactResult);
}

void ARProjectile::OnLevelUp(int OldLevel, int NewLevel)
{
	if(OldLevel == NewLevel)
	{
		return;
	}
	ProjectileMovement->Velocity = ProjectileMovement->Velocity * 1.5f;
}

void ARProjectile::DestroyProjectile()
{
	Destroy();
}

float ARProjectile::GetRadius()
{
	return InnerCollision->GetScaledSphereRadius();
}

UProjectileMovementComponent* ARProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovement;
}


