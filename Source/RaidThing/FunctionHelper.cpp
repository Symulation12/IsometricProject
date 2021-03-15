// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionHelper.h"

FunctionHelper::FunctionHelper()
{
}

FunctionHelper::~FunctionHelper()
{
}

float AngleBetweenVectors(FVector sourceVector, FVector targetVector)
{
	return acosf(FVector::DotProduct(sourceVector, targetVector));
}
