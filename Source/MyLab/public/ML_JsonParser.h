// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyLab.h"
#include "ML_ParserToCharacter.h"
#include "GameFramework/Actor.h"
#include "ML_JsonParser.generated.h"

UCLASS()
class MYLAB_API AML_JsonParser : public AActor, public IML_ParserToCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AML_JsonParser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
