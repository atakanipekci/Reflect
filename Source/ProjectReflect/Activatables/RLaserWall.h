// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "RIActivatable.h"
#include "ProjectReflect/TimeModify/RITimeModifiable.h"
#include "RLaserWall.generated.h"

UCLASS(Blueprintable)
class PROJECTREFLECT_API ARLaserWall : public AActor, public IRActivatable, public IRTimeModifiable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARLaserWall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Toggle();

	virtual bool Activate() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LaserCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpaceBetween = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LaserLength = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor PlayerLaserColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ProjectileLaserColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDamagePlayer = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDamageProjectile = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActive = true;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* LaserLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* LaserBeam;

private:

	bool TryDestroy(AActor* Hit);

	UPROPERTY()
	TArray<UNiagaraComponent*> Lasers;

	
};
