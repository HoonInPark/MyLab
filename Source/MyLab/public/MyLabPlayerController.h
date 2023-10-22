// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyLab.h"
#include "GameFramework/PlayerController.h"
#include "MyLabPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class MYLAB_API AMyLabPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
};
