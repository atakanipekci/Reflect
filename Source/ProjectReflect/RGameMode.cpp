// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameMode.h"

#include "LoadingScreenManager.h"
#include "Kismet/GameplayStatics.h"

void ARGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if(const UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		if(ULoadingScreenManager* LoadingScreenManager = GameInstance->GetSubsystem<ULoadingScreenManager>())
		{
			if (LoadingScreenManager)
			{
				LoadingScreenManager->RegisterLoadingProcessor(this);
			}
		}
	}

	//TODO need min loading duration so players can read tips etc, right now it can be instant
	bShowLoadingScreen = true;
	LoadSubLevel(1, true, true, this,"OnInitialSubLevelLoaded");
}

void ARGameMode::LoadSubLevel(int LevelId, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad, TObjectPtr<UObject> ObjToExecuteOn, FName CallBackFunctionName)
{
	const FString Path = "/Game/Maps/";
	const FString LevelName = FString::Printf(TEXT("Level%d"), LevelId);

	FLatentActionInfo Info;
	Info.CallbackTarget = this;
	Info.ExecutionFunction = CallBackFunctionName;
	Info.UUID = 1;
	Info.Linkage = 0;
	
	const FName AbsolutePath = FName(*(Path + LevelName));
	UGameplayStatics::LoadStreamLevel(GetWorld(), AbsolutePath, bMakeVisibleAfterLoad, bShouldBlockOnLoad, Info);
}

void ARGameMode::OnInitialSubLevelLoaded()
{
	bShowLoadingScreen = false;
	UE_LOG( LogStats, Warning, TEXT("OnSubLevelLoaded"));
}

bool ARGameMode::ShouldShowLoadingScreen(FString& OutReason) const
{
	OutReason = TEXT("Level is still loading");
	return bShowLoadingScreen;
}
