// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_DEMO_API UInteractComponent : public USphereComponent
{
	GENERATED_BODY()


	class ADoor* CurrentInteractiveOverlap;


public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor*  OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadWrite , EditAnywhere , Category = "Interacton Attributes ")
	class UAnimMontage* AnimMontage_Interact;


	void OnInteractiveOverlapped();
	void OnNoInteractive();

	class AFPS_Player* GetPlayer();

public:	


	/*
		will be called to make interaction with overlapped actors (this plays montage for it)
	*/
	void Start_Interact();

	/*
		will be called to make interaction with overlapped actors (excutes Interact Function on actors)
	*/
	UFUNCTION(BlueprintCallable)
	void Excute_Interact();


};
