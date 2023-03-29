// Fill out your copyright notice in the Description page of Project Settings.

#include "LauncherPlatform.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "ProjectReflect/Character/RCharacter.h"
#include "ProjectReflect/Components/ProjectileInteractor/RProjectileInteractorComponent.h"

// Sets default values
ALauncherPlatform::ALauncherPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileInteractionComponent = CreateDefaultSubobject<URProjectileInteractorComponent>(TEXT("Projectile Interactor"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALauncherPlatform::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ALauncherPlatform::OnOverlapEnd);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void ALauncherPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauncherPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ALauncherPlatform::Activate()
{
	bool bFlag = false;
	for (const auto Character : CharactersToLaunch)
	{
		Character->LaunchCharacter(LaunchVelocity, false, true);
		bFlag = true;
	}

	return bFlag;
}

void ALauncherPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG( LogStats, Warning, TEXT( "OnOverlapBegin: %s" ), *OtherActor->GetName());
	if(OtherActor)
	{
		if(const auto Character = Cast<ARCharacter>(OtherActor))
		{
			CharactersToLaunch.Add(Character);
		}
	}

	if(ActivateOnOverlap)
	{
		Activate();
	}

	// if (OtherComp->IsSimulatingPhysics())
	// {
	// 	UE_LOG( LogStats, Warning, TEXT( "AddFOrce: %s" ), *OtherComp->GetName());
	// 	OtherComp->AddImpulseAtLocation(GetVelocity() * 1000.0f, GetActorLocation());
	// }
	//
}

void ALauncherPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	if(OtherActor)
	{
		if(const auto Character = Cast<ARCharacter>(OtherActor))
		{
			CharactersToLaunch.Remove(Character);
		}
	}
}


