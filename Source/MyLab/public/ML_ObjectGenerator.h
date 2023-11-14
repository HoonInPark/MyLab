// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ML_ParserToCharacter.h"
#include "MyLab.h"
#include "GameFramework/Actor.h"
#include "ML_ObjectGenerator.generated.h"

UCLASS()
class MYLAB_API AML_ObjectGenerator : public AActor, public IML_ParserToCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AML_ObjectGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Object)
	TArray<TSoftObjectPtr<AActor>> BoundaryCubes;

private:
	virtual void ParserToObject_Implementation(FStaticData _StaticData) override;

};
