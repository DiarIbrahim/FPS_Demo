// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponManagerComponent.h"
#include "Player/FPS_Player.h"
#include "UI/GamePlayUI.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UWeaponManagerComponent::UWeaponManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	NumOnMagazine = magazineSize;


	// the Update UI
	if (GetPlayer()->GetGamePlayUI()) {
		GetPlayer()->GetGamePlayUI()->OnMagazineStausChanged(NumOnMagazine, magazineSize);
	}
	
}


float shootTimeCounter = 0.0f;
void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*
		time required between two shots
	*/
	if (!bCanshoot && shootTimeCounter <= .0f) {
		bCanshoot = true;
		shootTimeCounter = shootTime;
	}
	else {
		shootTimeCounter -= DeltaTime;
		bCanshoot = false;
	}


	/*
		shot while holding the trigger
	*/
	if (bWeaponSupportShootOnHold && bShootOnHold) {
		Shoot();
	}


}

void UWeaponManagerComponent::Shoot_Start()
{
	if (bWeaponSupportShootOnHold) {
		bShootOnHold = true;
	}
	else {
		Shoot();
	}
}

void UWeaponManagerComponent::Shoot_End()
{
	bShootOnHold = false;
}



void UWeaponManagerComponent::Shoot()
{
	if (!GetPlayer() || GetPlayer()->IsRunning() ||  bIsReloading ||  !bCanshoot || NumOnMagazine <= 0) return;
	

	// shoot performed
	NumOnMagazine--;

	if (AnimMontage_shoot) {
		GetPlayer()->PlayAnimMontage(AnimMontage_shoot);
	}
	GetPlayer()->AddControllerPitchInput(FMath::RandRange(-2.0f,0.9f));
	GetPlayer()->AddControllerYawInput(FMath::RandRange(-.5f,.5f));
	GetPlayer()->OnShoot_BP();

	if (APlayerController* pc = Cast<APlayerController>(GetPlayer()->GetController())) {
		pc->PlayerCameraManager->StartCameraShake(CameraShake_Shoot);
	}

	// the shoot performed
	if (GetPlayer()->GetGamePlayUI()) {
		GetPlayer()->GetGamePlayUI()->OnMagazineStausChanged(NumOnMagazine,magazineSize);
		GetPlayer()->GetGamePlayUI()->OnShoot();
	}


	// trace 

	FHitResult hit;
	FVector start = GetPlayer()->GetCamera()->GetComponentLocation();
	FVector end = start + GetPlayer()->GetCamera()->GetForwardVector() * 5000;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetPlayer());
	if(GetWorld()->LineTraceSingleByChannel(hit,start, end ,ECC_Visibility , params)){

		DrawDebugLine(GetWorld(),start,hit.ImpactPoint ,FColor::Green,0,5);
		DrawDebugPoint(GetWorld(),hit.ImpactPoint, 10,FColor::Red, 0, 5);
	}

}

AFPS_Player* UWeaponManagerComponent::GetPlayer()
{
	return Cast<AFPS_Player>(GetOwner());

}

void UWeaponManagerComponent::Reload()
{
	if (bIsReloading || NumOnMagazine == magazineSize || !AnimMontage_reload || !GetPlayer()) return;

	FName ReloadMontageSectionName = "";
	if (NumOnMagazine == 0)
		ReloadMontageSectionName = "full";
	else {
		ReloadMontageSectionName = FMath::RandBool() ? "v1" : "v2";
	}

	GetPlayer()->PlayAnimMontage(AnimMontage_reload,1,ReloadMontageSectionName);
	OnReloadStarted();

}

void UWeaponManagerComponent::OnReloadStarted()
{
	bIsReloading = true;
	
	if (GetPlayer()) {
		 GetPlayer()->GetGamePlayUI()->OnChangeFocus(0);
	}

}

void UWeaponManagerComponent::OnReloadFinished()
{
	bIsReloading = false;
	NumOnMagazine = magazineSize;


	// the Update bullet num on UI
	if (GetPlayer()->GetGamePlayUI()) {
		GetPlayer()->GetGamePlayUI()->OnMagazineStausChanged(NumOnMagazine, magazineSize);
		GetPlayer()->GetGamePlayUI()->OnChangeFocus(1);

	}
}


