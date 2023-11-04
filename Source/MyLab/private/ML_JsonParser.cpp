// Fill out your copyright notice in the Description page of Project Settings.


#include "ML_JsonParser.h"
#include "HttpModule.h"

namespace EQSDebug
{
	struct FItemData;
}

// Sets default values
AML_JsonParser::AML_JsonParser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AML_JsonParser::BeginPlay()
{
	Super::BeginPlay();
	
}

void AML_JsonParser::HttpCall(const FString& _InURL, const FString& _InVerb)
{
	const TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AML_JsonParser::OnResponseReceived);

	Request->SetURL(_InURL);
	Request->SetVerb(_InVerb);
	Request->SetHeader("Content-Type", TEXT("application/json"));

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	
}

void AML_JsonParser::OnResponseReceived(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful)
{
}
