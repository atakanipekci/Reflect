// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RIActivatable.h"
#include "GameFramework/Actor.h"
#include "RActivatableCable.generated.h"

UCLASS(Blueprintable)
class PROJECTREFLECT_API ARActivatableCable : public AActor, public IRActivatable
{
	GENERATED_BODY()
	
public:
	
	// Sets default values for this actor's properties
	ARActivatableCable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool Activate() override;

	virtual bool Deactivate() override;

	UFUNCTION(BlueprintCallable)
	virtual bool TryActivatingAttachedActor();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ActivateCable(bool bActivate);

public:	

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AActor* ActivatableActor;

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsActive = false;
};
