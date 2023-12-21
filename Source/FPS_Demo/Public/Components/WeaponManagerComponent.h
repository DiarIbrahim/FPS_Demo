// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_DEMO_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()


private:

	// internal variables

	// is used for multiple shoot while holing trigger
	bool bShootOnHold = false;
	bool bCanshoot = true;
	bool bIsReloading = false;


protected:

	/*
		the size of this weapons magazine
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | attributes")
	int32 magazineSize = 20;
	/*
	the number of bullets currently on magazine
*/
	int32 NumOnMagazine = 0;
	/*
	time needed between two shoots
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | attributes")
	float shootTime = 0.05;

	/*
		whether this weapon supports multiple shot on hold or not 
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | attributes")
	bool bWeaponSupportShootOnHold = false;

	//
	// montages
	//

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | Monages")
	class UAnimMontage* AnimMontage_shoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | Monages")
	class UAnimMontage* AnimMontage_reload;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | Camera Shakes")
	TSubclassOf<class UCameraShakeBase> CameraShake_Shoot;


	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// the socket name of the bone used as aim spot
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | Aim")
	FName AimSocketName;
	// offseting the aiming
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon | Aim")
	FVector AimOffset;


	// Sets default values for this component's properties
	UWeaponManagerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/*
		called for starting shoot on holding the button or single shot if  the weapon not supporting multiple shot on hold
	*/
	void Shoot_Start();
	
	/*
		called to stop hold to shoot
	*/
	void Shoot_End();


	/*
		shoot
	*/
	void Shoot();


	class AFPS_Player* GetPlayer();



	/*
		will be called when player presess button for reloading !
		this process cnnot be interrupted
	*/
	void Reload();

	/*
		called when this weapon started reloading, called from animBp
	*/
	void OnReloadStarted();
	/*
		this will be called by animNotifiers in AnimBP while reload finished
	*/
	UFUNCTION(BlueprintCallable)
	void OnReloadFinished();

	/*
		is reloading

	*/
	bool IsReloading() const { return bIsReloading; }

		
};
