// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileButton.h"

#include "ProjectReflect/Components/ProjectileInteractor/RProjectileInteractorComponent.h"

// Sets default values
ARProjectileButton::ARProjectileButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileInteractionComponent = CreateDefaultSubobject<URProjectileInteractorComponent>(TEXT("Projectile Interactor"));
	ProjectileInteractionComponent->OnProjectileHitDelegate.AddDynamic(this, &ARProjectileButton::OnProjectileHit);
}

// Called when the game starts or when spawned
void ARProjectileButton::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARProjectileButton::OnProjectileHit(ARProjectile* Projectile, const FHitResult& Hit)
{
	Activate();
}

void ARProjectileButton::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ARProjectileButton, ActorsToActivate))
	{
		int ChangedIndex = PropertyChangedEvent.GetArrayIndex(PropertyChangedEvent.GetPropertyName().ToString());

		switch(PropertyChangedEvent.ChangeType)
		{
			case EPropertyChangeType::ArrayAdd :
				Cables.EmplaceAt(ChangedIndex, GetWorld()->SpawnActor<ARSplineActor>(CableActorClass, GetActorTransform()));
			break;

			case EPropertyChangeType::ValueSet :
				{
					if(!Cables.IsValidIndex(ChangedIndex) || Cables[ChangedIndex] == nullptr || ActorsToActivate[ChangedIndex] == nullptr)
					{
						return;
					}
				
					ARSplineActor* Cable = Cables[ChangedIndex];
					Cable->ClearNodes();
					FVector EndPosition = ActorsToActivate[ChangedIndex]->GetActorLocation();
					float Dist = FVector::Dist(GetActorLocation(), EndPosition);
					int NodeCount = Dist/Cable->NodeDistance;

					FVector Direction = EndPosition - GetActorLocation();
					Direction.Normalize();
					Cable->AddNode(GetActorLocation());
					for(int i = 0; i < NodeCount; i++)
					{
						Cable->AddNode(GetActorLocation() + Direction*Cable->NodeDistance*(i+1));
					}
					Cable->AddNode(EndPosition);
					Cable->UpdateSpline();
				}
			break;

			case EPropertyChangeType::ArrayRemove:
				if(!Cables.IsValidIndex(ChangedIndex))
				{
					return;
				}

				if(Cables[ChangedIndex])
				{
					Cables[ChangedIndex]->Destroy();
				}

				Cables.RemoveAt(ChangedIndex);
			break;

			case EPropertyChangeType::ArrayClear:
				if(!Cables.IsValidIndex(ChangedIndex) || Cables[ChangedIndex] == nullptr)
				{
					return;
				}

				for (auto Cable : Cables)
				{
					Cable->Destroy();
				}
			break;
			
			default:
				UE_LOG(LogTemp,Warning,TEXT("ARProjectileButton::PostEditChangeProperty unhandled case for cable"))
			break;
		}
	}
}

// Called every frame
void ARProjectileButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ARProjectileButton::Activate()
{
	bool bFlag = false;
	for (auto Actor : ActorsToActivate)
	{
		IRActivatable* Interactable = Cast<IRActivatable>(Actor);
		if(Interactable)
		{
			Interactable->Activate();
			bFlag = true;
		}
	}

	return bFlag;
}

bool ARProjectileButton::Deactivate()
{
	bool bFlag = false;
	for (auto Actor : ActorsToActivate)
	{
		IRActivatable* Interactable = Cast<IRActivatable>(Actor);
		if(Interactable)
		{
			Interactable->Deactivate();
			bFlag = true;
		}
	}

	return bFlag;
}

