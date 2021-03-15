// Fill out your copyright notice in the Description page of Project Settings.


#include "TransparencyMesh.h"

// Sets default values for this component's properties
UTransparencyMesh::UTransparencyMesh()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Set default?
	/*static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Geometry/Meshes/CubeMaterial_Transparent.CubeMaterial_Transparent'"));
	if (Material.Succeeded()) {
		UMaterialInterface a();
		
		//transparentMaterials.Add(UMaterialInterface::UMaterialInterface(Material.Object));
	}
	*/
	// ...
}


// Called when the game starts
void UTransparencyMesh::BeginPlay()
{
	Super::BeginPlay();

	//Setup
	mesh = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (IsValid(mesh))
	{
		defaultMaterials = mesh->GetMaterials();
	}
	

	// ...
	
}

void UTransparencyMesh::StopFading()
{
	if (!IsValid(mesh)) return;
	if (defaultMaterials.Num() <= 0) return;
	if (instanceList.Num() <= 0) return;
	fading = false;
	SetComponentTickEnabled(true);


}

void UTransparencyMesh::BeginFading()
{
	if (!IsValid(mesh)) return;
	if (transparentMaterials.Num() <= 0) return;
	if (instanceList.Num() <= 0) { // List is empty

		for(auto i : transparentMaterials)
		{ 
			UMaterialInstanceDynamic* toAdd = UMaterialInstanceDynamic::Create(i, this);
			instanceList.Add(toAdd);
		}

	}
	//List is now populated or was already populated
	for (int i = 0; i < instanceList.Num(); i++)
	{
		mesh->SetMaterial(i, instanceList[i]);
	}
	fading = true;
	SetComponentTickEnabled(true);



}


void UTransparencyMesh::SetDefaultMaterials() 
{
	if (!IsValid(mesh)) return;
	if (defaultMaterials.Num() <= 0) return;

	for (int i = 0; i < defaultMaterials.Num(); i++)
	{
		mesh->SetMaterial(i, defaultMaterials[i]);
	}
}

// Called every frame
void UTransparencyMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Update Transparency
	currentTransparency = FMath::FInterpTo(currentTransparency, (fading ? 1 : 0), DeltaTime, fadeSpeed);

	//Update materials
	for (auto i : instanceList)
	{
		i->SetScalarParameterValue("Fade", FMath::InterpEaseInOut(0.f,maxTransparency,currentTransparency,2.f));
	}

	if (fading)
	{
		//Fully Faded
		if (currentTransparency >= 1) SetComponentTickEnabled(false);
	}
	else 
	{
		//Fully opaque, reset materials
		if (currentTransparency <= 0)
		{
			SetComponentTickEnabled(false);
			SetDefaultMaterials();
		}
	}


	// ...
}

