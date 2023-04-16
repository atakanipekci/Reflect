// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <stdbool.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectReflect/Activatables/RActivatableCable.h"
#include "ProjectReflect/Activatables/RIActivatable.h"
#include "ProjectReflect/Utility/RSplineActor.h"
#include "RProjectileButton.generated.h"

UCLASS()
class PROJECTREFLECT_API ARProjectileButton : public AActor, public IRActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARProjectileButton();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Activate() override;
	virtual bool Deactivate() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(class ARProjectile* Projectile, const FHitResult& Hit);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditFixedOrder))
	TArray<AActor*> ActorsToActivate;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARActivatableCable> CableActorClass;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class URProjectileInteractorComponent* ProjectileInteractionComponent;

	UPROPERTY()
	TArray<ARActivatableCable*> Cables;

	bool bIsActivated = false;
};
