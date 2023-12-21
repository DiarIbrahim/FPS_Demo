// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

static void print(FString str, int32 key = -1) {
	GEngine->AddOnScreenDebugMessage(key, 5, FColor::Red, str);
}