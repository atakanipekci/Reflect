// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadingProcessInterface.h"
#include "GameFramework/GameMode.h"
#include "RGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API ARGameMode : public AGameMode, public ILoadingProcessInterface
{
	GENERATED_BODY()

	
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	void LoadSubLevel(int LevelId, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, TObjectPtr<UObject> ObjToExecuteOn, FName CallBackFunctionName);

	UFUNCTION()
	void OnInitialSubLevelLoaded();

	virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;

	bool bShowLoadingScreen;
};
