// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyLab.h"
#include "UObject/Interface.h"
#include "ML_ParserToCharacter.generated.h"

USTRUCT(BlueprintType)
struct FStaticData
{
	GENERATED_BODY()

	FString Id;
	TMultiMap<FString, FString> Data;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UML_ParserToCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYLAB_API IML_ParserToCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void ParserToObject(FStaticData _StaticData);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void ParserToCharacter(FStaticData _StaticData);

	// int32 num_cycle{ 1 };
};
