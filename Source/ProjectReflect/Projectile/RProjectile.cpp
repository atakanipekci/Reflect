// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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

	// OuterCollision = CreateDefaultSubobject<USphereComponent>(TEXT("OuterCollision"));
	// OuterCollision->InitSphereRadius(50.0f);
	// OuterCollision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	// OuterCollision->CanCharacterStepUpOn = ECB_No;
	// OuterCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	// OuterCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// OuterCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	// OuterCollision->AttachToComponent(InnerCollision, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = InnerCollision;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &ARProjectile::OnBounce);
	ProjectileMovement->OnProjectileStop.AddDynamic(this, &ARProjectile::OnStop);
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 1;
	ProjectileMovement->Friction = 0;
	// ProjectileMovement->bRotationFollowsVelocity = true;//creates twitching
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
	
	// if(GetLifeSpan() <= 0) return;
	//
	// if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	// {
	// 	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	//
	// 	SetLifeSpan(5);
	// 	
	// }
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

void ARProjectile::DestroyProjectile()
{
	Destroy();
}

UProjectileMovementComponent* ARProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovement;
}


