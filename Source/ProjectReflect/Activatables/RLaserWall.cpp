// Fill out your copyright notice in the Description page of Project Settings.


#include "RLaserWall.h"

#include "ProjectReflect/Character/RCharacter.h"
#include "ProjectReflect/Projectile/RProjectile.h"
#include "ProjectReflect/Utility/CollisionProfileNames.h"

// Sets default values
ARLaserWall::ARLaserWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Laser Location"));
	
}

// Called when the game starts or when spawned
void ARLaserWall::BeginPlay()
{
	Super::BeginPlay();
	Lasers.Reserve(LaserCount);
	for(int i = 0; i < LaserCount; i++)
	{
		Lasers.Emplace(nullptr);
	}
}

bool ARLaserWall::TryDestroy(AActor* Hit)
{
	if(bDamagePlayer)
	{
		if(ARCharacter* Character = Cast<ARCharacter>(Hit))
		{
			Character->Death();
			return true;
		}
	}
	else if(bDamageProjectile)
	{
		if(ARProjectile* Projectile = Cast<ARProjectile>(Hit))
		{
			Projectile->DestroyProjectile();
			return true;
		}
	}

	return false;
}

// Called every frame
void ARLaserWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!LaserLocation)
	{
		return;
	}
	
	for(int i = 0; i < LaserCount; i++)
	{
		FHitResult HitResult;
		FVector SourceLocation = LaserLocation->GetComponentLocation() + FVector(0,0, i*SpaceBetween);
		FVector EndLocation = SourceLocation + LaserLocation->GetForwardVector()*LaserLength;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		ECollisionChannel Channel;
		if(bDamageProjectile)
		{
			Channel =COLLISION_PROJECTILE;
		}
		else
		{
			Channel = ECC_Pawn;
		}
		GetWorld()->LineTraceSingleByChannel(HitResult,SourceLocation,EndLocation, Channel, Params);

		FVector HitLocation = EndLocation;

		if(HitResult.IsValidBlockingHit() && bActive)
		{
			HitLocation = HitResult.ImpactPoint;
			TryDestroy(HitResult.GetActor());
		}

		if(LaserBeam)
		{
			if(!Lasers[i])
			{
				Lasers[i] = UNiagaraFunctionLibrary::SpawnSystemAttached(LaserBeam, LaserLocation, NAME_None, SourceLocation, LaserLocation->GetForwardVector().Rotation(), EAttachLocation::KeepWorldPosition, true);
				if(bDamageProjectile)
				{
					Lasers[i]->SetNiagaraVariableLinearColor(FString("User.Color"), ProjectileLaserColor);
				}
				else
				{
					Lasers[i]->SetNiagaraVariableLinearColor(FString("User.Color"), PlayerLaserColor);
				}
			}
			FVector RelativeLocation = LaserLocation->GetComponentTransform().InverseTransformPosition(HitLocation - FVector(0,0, i*SpaceBetween));
			if(!bActive)
			{
				RelativeLocation = FVector::ZeroVector;
			}
			Lasers[i]->SetNiagaraVariablePosition(FString("User.Beam End"), RelativeLocation);
		}
		
		/*DrawDebugLine(
			GetWorld(),
			SourceLocation,
			HitLocation,
			FColor(255, 0, 0),
			false, -1, 0,
			12.333
		);*/
	}
}

void ARLaserWall::Toggle()
{
	bActive = !bActive;
}

bool ARLaserWall::IActivate()
{
	Toggle();
	return true;
}

