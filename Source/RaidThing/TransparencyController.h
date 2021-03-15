// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <RaidThing/TransparencyMesh.h>
#include "TransparencyController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAIDTHING_API UTransparencyController : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UTransparencyController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	APlayerCameraManager* camera;
	APawn* pawn;
	TArray<UTransparencyMesh*> tMeshList;
	TArray<UTransparencyMesh*> tMeshListCurrent;

	bool checkVelocity;
	float fadeRadius = 150;
	float velocityMax = 300;
	float velocityMultiplier = 0.75;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<UTransparencyMesh*> CheckTransparencyMeshes(float DeltaTime);
	bool ShouldCheckVelocityFade(FVector* v);

		
};
