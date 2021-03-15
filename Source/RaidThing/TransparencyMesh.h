// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransparencyMesh.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class RAIDTHING_API UTransparencyMesh : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTransparencyMesh();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMaterialInterface*> transparentMaterials;


	void BeginFading();
	void StopFading();
	void SetDefaultMaterials();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UStaticMeshComponent* mesh;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TArray<UMaterialInterface*> defaultMaterials;
	TArray<UMaterialInstanceDynamic*> instanceList;
	bool fading = false;
	float currentTransparency = 0;
	float maxTransparency = 0.75;
	float fadeSpeed = 3;

		
};
