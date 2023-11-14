// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyLab.h"
#include "ML_ParserToCharacter.h"
#include "Interfaces/IHttpRequest.h"
#include "Http.h"
#include "GameFramework/Actor.h"
#include "ML_JsonParser.generated.h"

class FJsonObject;

UENUM(BlueprintType)
enum class EEndPtType : uint8
{
	STR UMETA(DisplayName = "STRING"),
	STR_ARR UMETA(DisplayName = "STRING_ARRAY"),
	NUM UMETA(DisplayName = "NUMBER")
};

UCLASS()
class MYLAB_API AML_JsonParser : public AActor, public IML_ParserToCharacter
{
	GENERATED_BODY()

public:
	FHttpModule* Http;
	// Sets default values for this actor's properties
	AML_JsonParser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void HttpCall(FString _URL, FString _Type);
	void OnResponseReceived(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful);

	void JasonParser(const TSharedRef<TJsonReader<>>& _Reader, EEndPtType _EndPtType);
	void ParserInParser(const TMap<FString, TSharedPtr<FJsonValue>>& _JsonMap, EEndPtType _EndPtType);
	
private:
	virtual void ParserToObject_Implementation(FStaticData _StaticData) override;
	virtual void ParserToCharacter_Implementation(FStaticData _StaticData) override;
};
