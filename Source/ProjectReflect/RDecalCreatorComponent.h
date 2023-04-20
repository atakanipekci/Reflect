// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RDecalCreatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URDecalCreatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URDecalCreatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void CreateDecal(AActor* Actor, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UMaterialInterface* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FVector Size = FVector(10, 10, 10);

	UPROPERTY(EditDefaultsOnly, Category = Config)
	int MaxActiveDecalCount = 10;

private:
	TQueue<class ADecalActor*> DecalInstanceQueue;
	int DecalInstanceCount;
};
