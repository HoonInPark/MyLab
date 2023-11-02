// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyLab.h"
#include "GameFramework/GameModeBase.h"
#include "MyLabGameMode.generated.h"

UCLASS(minimalapi)
class AMyLabGameMode : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	AMyLabGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WebBrowser", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> WebBrowserWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

};
