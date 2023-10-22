// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyLabGameMode.h"
#include "MyLabCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyLabGameMode::AMyLabGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
