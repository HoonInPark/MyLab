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
	JasonParser(Reader, EEndPtType::STR_ARR);
}

void AML_JsonParser::JasonParser(const TSharedRef<TJsonReader<>>& _Reader, EEndPtType _EndPtType)
{
	FStaticData StaticData;

	TSharedPtr<FJsonValue> JasonValue;
	if (!FJsonSerializer::Deserialize(_Reader, JasonValue)) return;

	const auto& JasonArr_temp = JasonValue->AsArray();
	for (auto& JasonVal : JasonArr_temp)
	{
		// 다음과 같이 하면 첫번째 층위의 필드에 접근할 수 있다.
		const auto& JasonMap_temp = JasonVal->AsObject()->Values;
		ParserInParser(JasonMap_temp, _EndPtType);
	}
}

void AML_JsonParser::ParserInParser(const TMap<FString, TSharedPtr<FJsonValue>>& _JsonMap, EEndPtType _EndPtType)
{
	for (auto& JasonElem : _JsonMap)
	{
		EJson EndPtType;
		
		switch (_EndPtType)
		{
		case EEndPtType::STR:
			EndPtType = EJson::String;
			break;
		case EEndPtType::STR_ARR:
			EndPtType = EJson::Array;
			break;
		case EEndPtType::NUM:
			EndPtType = EJson::Number;
			break;
		default: ;
		}
		
		if (EndPtType == JasonElem.Value->Type) // 우리의 경우, JasonElem.Value->Type이 Array인 경우를 목적지로 삼는다.
		{
			MLLOG_S(Warning)
		}
		else if (EJson::Object == JasonElem.Value->Type)
			ParserInParser(JasonElem.Value->AsObject()->Values, _EndPtType);
	}
}

void AML_JsonParser::ParserToObject_Implementation(FStaticData _StaticData)
{
}

void AML_JsonParser::ParserToCharacter_Implementation(FStaticData _StaticData)
{
}
