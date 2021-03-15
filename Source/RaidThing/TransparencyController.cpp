// Fill out your copyright notice in the Description page of Project Settings.


#include "TransparencyController.h"
#include <RaidThing/TransparencyMesh.h>

// Sets default values for this component's properties
UTransparencyController::UTransparencyController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTransparencyController::BeginPlay()
{
	Super::BeginPlay();

	//Setup

	pawn = Cast<APawn>(GetOwner());
	camera = Cast<APlayerController>(pawn->GetController())->PlayerCameraManager;
	// ...
	
}

TArray<UTransparencyMesh*> UTransparencyController::CheckTransparencyMeshes(float DeltaTime)
{
	TArray<UTransparencyMesh*> fadeComponents;
	if (!IsValid(pawn) || !IsValid(camera)) return fadeComponents;
	
	FVector start = camera->GetCameraLocation();
	FVector end = pawn->GetActorLocation();
	FVector vel = pawn->GetVelocity();
	FVector dir = start - end;
	dir.Normalize();
	end = (dir*fadeRadius) + end;

	FCollisionShape sphere = FCollisionShape::MakeSphere(fadeRadius);
	TArray<FHitResult> hits;
	FCollisionQueryParams options(FName(TEXT("sweepA")),false,GetOwner());
	options.AddIgnoredActor(pawn);
	GetWorld()->SweepMultiByChannel(hits, start, end, FQuat::Identity, ECC_Camera, sphere);
	for (auto i : hits)
	{
		UTransparencyMesh* tM = Cast<UTransparencyMesh>(i.Actor->GetComponentByClass(UTransparencyMesh::StaticClass()));
		if (IsValid(tM)) fadeComponents.Add(tM);
	}
	hits.Empty();
	if (ShouldCheckVelocityFade(&vel))
	{
		FVector clamped = (vel * velocityMultiplier).GetClampedToSize(0, velocityMax);

		GetWorld()->SweepMultiByChannel(hits, start + clamped, end + clamped, FQuat::Identity, ECC_Camera, sphere);

		for (auto i : hits)
		{
			UTransparencyMesh* tM = Cast<UTransparencyMesh>(i.Actor->GetComponentByClass(UTransparencyMesh::StaticClass()));
			if (IsValid(tM)) fadeComponents.Add(tM);
		}

	}


	return fadeComponents;

}


bool UTransparencyController::ShouldCheckVelocityFade(FVector* v)
{
	if (v->SizeSquared() > 0 && checkVelocity)
		return true;
	return false;
}


// Called every frame
void UTransparencyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TArray<UTransparencyMesh*> desiredList = CheckTransparencyMeshes(DeltaTime);
	TArray<UTransparencyMesh*> currentList = tMeshListCurrent;

	if (desiredList != currentList)
	{
		for (auto i : currentList)
		{
			//Stop the fading process and remove from the list if it shouldn't be fading anymore
			if (!desiredList.Contains(i))
			{
				i->StopFading();
				tMeshListCurrent.Remove(i);
			}
		}

		for (auto i : desiredList)
		{
			if (!tMeshListCurrent.Contains(i))
			{
				i->BeginFading();
				tMeshListCurrent.Add(i);
			}
		}
	}
	// ...
}

