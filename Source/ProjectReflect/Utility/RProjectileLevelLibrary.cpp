// Fill out your copyright notice in the Description page of Project Settings.


#include "RProjectileLevelLibrary.h"
#include "ProjectReflect/Data/RLevelUpData.h"
#include "ProjectReflect/Components/RLevelComponent.h"

bool URProjectileLevelLibrary::TryLevelUpActor(AActor* Actor)
{
	if(Actor == nullptr)
	{
		return false;
	}

	URLevelComponent* LevelComponent = Actor->FindComponentByClass<URLevelComponent>();
	return LevelComponent->LevelUp();
}

void URProjectileLevelLibrary::SetActorColorByLevel(AActor* Actor, int Level)
{
	if(Actor == nullptr)
	{
		return;
	}
	
	UMeshComponent* MeshComponent = Cast<UMeshComponent>(Actor->GetComponentByClass(UMeshComponent::StaticClass()));
	if(MeshComponent == nullptr)
	{
		return;
	}
	
	const URLevelUpData* GlobalLevelAsset = LoadObject<URLevelUpData>(nullptr, TEXT("/Script/ProjectReflect.RLevelUpData'/Game/Data/LevelUp/DA_GlobalLevelUp.DA_GlobalLevelUp'"));
	if(GlobalLevelAsset)
	{
		UMaterialInstance* MaterialInstance = GlobalLevelAsset->GetLevelMaterial(Level);
		MeshComponent->SetMaterial(0, MaterialInstance);
	}
}
