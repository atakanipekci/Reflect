// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTREFLECT_API URMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	void OnStartClicked();
	void AsyncLevelLoadFinished(const FString& Name);

	virtual void NativeConstruct() override;
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;
};
