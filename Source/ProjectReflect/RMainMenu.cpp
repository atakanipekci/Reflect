// Fill out your copyright notice in the Description page of Project Settings.


#include "RMainMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URMainMenu::OnStartClicked()
{
	const FString Path = "/Game/Maps/";
	const FString LevelName = "IntroLevel";
	UGameplayStatics::OpenLevel(this, FName(*LevelName));

	//TODO try cache sub level aswell 
	// LoadPackageAsync(Path + LevelName, FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result)
	// {
	// 	if(Result == EAsyncLoadingResult::Succeeded)
	// 	{
	// 		AsyncLevelLoadFinished(LevelName);
	// 	}
	// }), 0 , PKG_ContainsMap);
}

void URMainMenu::AsyncLevelLoadFinished(const FString& LevelName)
{
	// UGameplayStatics::OpenLevel(this, FName(*LevelName));//Path kullan
}

void URMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &URMainMenu::OnStartClicked);
}
