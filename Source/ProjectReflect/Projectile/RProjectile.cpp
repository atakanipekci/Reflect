// Fill out your copyright notice in the Description page of Project Settings.

#include "RProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectReflect/Components/RDamageComponent.h"
#include "ProjectReflect/Components/RLevelComponent.h"
#include "ProjectReflect/Components/ProjectileInteractor/RProjectileInteractorComponent.h"
#include "ProjectReflect/Utility/CollisionProfileNames.h"

ARProjectile::ARProjectile() 
{
	PrimaryActorTick.bCanEverTick = true;
	
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

void ARProjectile::BeginPlay()
{
	Super::BeginPlay();

	Mesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if(Mesh)
	{
		InitializedScale = Mesh->GetRelativeScale3D();
	}
}

void ARProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(InitializedLifeSpan <= 0)
	{
		return;
	}
	
	if(Mesh)
	{
		float CurrentLife = GetLifeSpan();
		float LifeTimeRatio = CurrentLife / InitializedLifeSpan;
		Mesh->SetWorldScale3D(InitializedScale*LifeTimeRatio);
	}
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

	ResetLifeSpan();

	if(BounceSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), BounceSound, ImpactResult.Location, ImpactResult.ImpactNormal.Rotation(), 1, 1, 0, BounceSound->AttenuationSettings);
	}
	
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
	int LevelDiff = NewLevel - OldLevel;
	if(LevelDiff <= 0)
	{
		return;
	}
	
	ProjectileMovement->Velocity = ProjectileMovement->Velocity * 1.5f * LevelDiff;
	
	DamageComponent->IncreaseDamage(LevelDiff);
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

void ARProjectile::SetLifeSpan(float InLifespan)
{
	Super::SetLifeSpan(InLifespan);

	InitializedLifeSpan = InLifespan;
}


