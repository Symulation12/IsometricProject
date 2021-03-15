// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RAIDTHING_API FunctionHelper
{
public:
	FunctionHelper();
	~FunctionHelper();

	UFUNCTION(BlueprintPure, Category = "Helper")
		static float AngleBetweenVectors(
		UPARAM(DisplayName="Source Vector") FVector sourceVector,
		UPARAM(DisplayName = "Target Vector") FVector targetVector);
};
