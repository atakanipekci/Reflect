// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectReflect/Activatables/RIActivatable.h"
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
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnProjectileHit(class ARProjectile* Projectile, const FHitResult& Hit);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> ActorsToActivate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class URProjectileInteractorComponent* ProjectileInteractionComponent; 
};
