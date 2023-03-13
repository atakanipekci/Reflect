// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RLifeComponent.generated.h"

//Probably going to need more info and/or more delegates later
DECLARE_MULTICAST_DELEGATE(FHealthReachedZero)
DECLARE_MULTICAST_DELEGATE_TwoParams(FTookDamage, FHitResult HitResult, bool bKilled)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTREFLECT_API URLifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URLifeComponent();

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FHealthReachedZero HealthReachedZero;
	FTookDamage TookDamage;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHealth = 1.0f;

	//Min damage required to actually deal damage to this component
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DamageThreshold = 1.0f;

private:
	float CurrentHealth;

		
};
