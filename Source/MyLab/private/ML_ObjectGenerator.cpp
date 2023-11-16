// Fill out your copyright notice in the Description page of Project Settings.


#include "ML_ObjectGenerator.h"

// Sets default values
AML_ObjectGenerator::AML_ObjectGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AML_ObjectGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AML_ObjectGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AML_ObjectGenerator::ParserToObject_Implementation(FStaticData _StaticData)
{
}

