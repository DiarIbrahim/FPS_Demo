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


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USphereComponent* collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* DoorHolder;
	UPROPERTY(BlueprintReadWrite ,EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere , Category = "Door | Attributes")
	bool bFlipOpenningDir = false;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void Interact();

	// called when interact started
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

};
