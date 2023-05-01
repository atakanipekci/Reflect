// Fill out your copyright notice in the Description page of Project Settings.


#include "RDestructibleActor.h"

#include "Engine/DamageEvents.h"

// Sets default values
ARDestructibleActor::ARDestructibleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeComponent = CreateDefaultSubobject<URLifeComponent>(TEXT("Life Component"));
	LevelComponent = CreateDefaultSubobject<URLevelComponent>(TEXT("Level Component"));
	LevelComponent->OnLevelUp.AddDynamic(this, &ARDestructibleActor::OnLevelUp);
}

void ARDestructibleActor::PostInitProperties()
{
	Super::PostInitProperties();
}

bool ARDestructibleActor::IActivate()
{
	Explode(GetActorLocation());
	return true;
}

// Called when the game starts or when spawned
void ARDestructibleActor::BeginPlay()
{
	Super::BeginPlay();
	LifeComponent->TookDamage.AddUObject(this, &ARDestructibleActor::Damaged);
	
}

void ARDestructibleActor::OnLevelUp(int OldLevel, int NewLevel)
{
	LifeComponent->DamageThreshold = NewLevel+1;
}

// Called every frame
void ARDestructibleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARDestructibleActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return LifeComponent->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ARDestructibleActor::Damaged(FHitResult HitResult, bool bKilled)
{
	if(bKilled)
	{
		Explode(HitResult.ImpactPoint);
	}
}


