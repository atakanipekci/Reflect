// Fill out your copyright notice in the Description page of Project Settings.


#include "RDecalCreatorComponent.h"

#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
URDecalCreatorComponent::URDecalCreatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URDecalCreatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URDecalCreatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URDecalCreatorComponent::CreateDecal(AActor* Actor, const FHitResult& Hit)
{
	const auto Decal = GetWorld()->SpawnActor<ADecalActor>(Hit.Location, UKismetMathLibrary::MakeRotFromZ(Hit.Normal));
	if (Decal && DecalMaterial)
	{
		DecalInstanceCount++;
		Decal->SetDecalMaterial(DecalMaterial);
		Decal->GetDecal()->DecalSize = Size;
		DecalInstanceQueue.Enqueue(Decal);

		if(DecalInstanceCount > MaxActiveDecalCount && !DecalInstanceQueue.IsEmpty())
		{
			auto QueueItemPointer = DecalInstanceQueue.Peek();
			if(QueueItemPointer)
			{
				auto Instance = *QueueItemPointer;
				DecalInstanceQueue.Pop();
				if(Instance != nullptr)
				{
					Instance->Destroy();
				}
			}
			

			
		}
	}
}
