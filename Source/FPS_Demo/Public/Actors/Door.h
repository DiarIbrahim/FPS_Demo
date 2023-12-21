// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class FPS_DEMO_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	bool bIsOpen = false;

	// Components


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	
	// colision, this door will be detected based on this collsion's overlap
	class USphereComponent* collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)

	// holds and rotates the door, this allows to move the door freely regardless of its pivot
	USceneComponent* DoorHolder;
	// the actual door mesh
	UPROPERTY(BlueprintReadWrite ,EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	// whether to invers the opening direction
	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "Door | Attributes")
	bool bFlipOpenningDir = false;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// can be called to make interaction on this door
	UFUNCTION(BlueprintCallable)
	void Interact();

	// called when interact started
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

};
