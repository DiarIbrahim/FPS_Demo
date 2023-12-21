// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Door.h"
#include "Components/sphereComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	if (!root) {
		root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
		SetRootComponent(root);
	}

	if (!collision) {
		collision  = CreateDefaultSubobject<USphereComponent>(FName("collision"));
		collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		collision->SetCollisionProfileName("OverlapAll");
		SetRootComponent(root);
	}

	if (!DoorHolder) {
		DoorHolder = CreateDefaultSubobject<USceneComponent>(FName("Door Holder"));
		DoorHolder->SetupAttachment(root);
	}

	if (!DoorMesh) {
		DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Door Mesh"));
		DoorMesh->SetupAttachment(DoorHolder);
		DoorMesh->SetMobility(EComponentMobility::Movable);
	}

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpen && !FMath::IsNearlyEqual(DoorHolder->GetRelativeRotation().Yaw , bFlipOpenningDir ? 90 : -90 , 0.005)) {
		DoorHolder->SetRelativeRotation(FRotator(0, FMath::Lerp(DoorHolder->GetRelativeRotation().Yaw , bFlipOpenningDir ? 90 : -90 , DeltaTime*10), 0));
	}
	else if(!bIsOpen && !FMath::IsNearlyEqual(DoorHolder->GetRelativeRotation().Yaw, 0, 0.005)){
		DoorHolder->SetRelativeRotation(FRotator(0, FMath::Lerp(DoorHolder->GetRelativeRotation().Yaw, 0, DeltaTime * 10), 0));

	}

}

void ADoor::Interact()
{
	bIsOpen = !bIsOpen;
	OnInteract();
}

