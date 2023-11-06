// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyLab.h"
#include "ML_ParserToCharacter.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IHttpRequest.h"
#include "ML_JsonParser.generated.h"

class FHttpModule;

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
	UFUNCTION()
	void HttpCall(const FString& _InURL, const FString& _InVerb);
	void OnResponseReceived(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful);
	
private:
	FHttpModule* Http;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString URL;
	
	FString GetResponse;

};
