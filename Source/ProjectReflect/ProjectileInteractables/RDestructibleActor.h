// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectReflect/Activatables/RIActivatable.h"
#include "ProjectReflect/Components/RLifeComponent.h"
#include "RDestructibleActor.generated.h"

UCLASS()
class PROJECTREFLECT_API ARDestructibleActor : public AActor, public IRActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARDestructibleActor();
	virtual void PostInitProperties() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void Damaged(FHitResult HitResult, bool bKilled);

	UFUNCTION(BlueprintImplementableEvent)
	void Explode(const FVector& HitAt);

	virtual bool Activate() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	URLifeComponent* LifeComponent;
};
