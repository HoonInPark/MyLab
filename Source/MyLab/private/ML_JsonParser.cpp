// Fill out your copyright notice in the Description page of Project Settings.


#include "ML_JsonParser.h"

namespace EQSDebug
{
	struct FItemData;
}

// Sets default values
AML_JsonParser::AML_JsonParser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AML_JsonParser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AML_JsonParser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

