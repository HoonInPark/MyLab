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
	PrimaryActorTick.bCanEverTick = false;

	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AML_JsonParser::BeginPlay()
{
	Super::BeginPlay();

	HttpCall(TEXT("http://52.79.98.84/entities"), TEXT("GET"));
}

void AML_JsonParser::HttpCall(FString _URL, FString _Type)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AML_JsonParser::OnResponseReceived);

	Request->SetURL(_URL);
	Request->SetVerb(_Type);
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void AML_JsonParser::OnResponseReceived(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful)
{
	if (200 != _Response->GetResponseCode()) return;
	const FString ResponseBody = _Response->GetContentAsString();
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);
	JsonParser(Reader, EEndPtType::STR_ARR);
}

bool AML_JsonParser::JsonParser(const TSharedRef<TJsonReader<>>& _Reader, EEndPtType _EndPtType)
{
	TSharedPtr<FJsonValue> JsonValue;
	if (!FJsonSerializer::Deserialize(_Reader, JsonValue)) return false;

	switch (_EndPtType) {
	case EEndPtType::STR:
		break;
	case EEndPtType::STR_ARR:
		for (auto Iter = JsonValue->AsArray().CreateConstIterator(); Iter; ++Iter)
		{
			(*Iter)->AsObject()->Values;
		}
		
		break;
	case EEndPtType::NUM:
		break;
	default: ;
	}
	
	return false;
}

void AML_JsonParser::ParseToSend_Implementation(FStaticData _StaticData)
{
	
}
