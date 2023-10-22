// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(MyLab, Log, All);
#define MLLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define MLLOG_S(Verbosity) UE_LOG(MyLab, Verbosity, TEXT("%s"), *MLLOG_CALLINFO)
#define MLLOG(Verbosity, Format, ...) UE_LOG(MyLab, Verbosity, TEXT("%s%s"), *MLLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define MLCHECK(Expr, ...)	{ if(!(Expr)) {MLLOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__; }}