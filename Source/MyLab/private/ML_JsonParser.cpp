// Fill out your copyright notice in the Description page of Project Settings.


#include "ML_JsonParser.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

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

	HttpCall(TEXT("http://52.79.98.84/entities"), "GET");
}

void AML_JsonParser::HttpCall(const FString& _InURL, const FString& _InVerb)
{
	const TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AML_JsonParser::OnResponseReceived);

	Request->SetURL(_InURL);
	Request->SetVerb(_InVerb); // 인수로 들어갈 수 있는 것들에는 "GET", "POST", "PUT", "DELETE"가 있다.
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->ProcessRequest();
}

void AML_JsonParser::OnResponseReceived(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(_Response->GetContentAsString());

	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) return;
	GetResponse = *_Response->GetContentAsString();
}
