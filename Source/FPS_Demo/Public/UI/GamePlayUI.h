// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayUI.generated.h"

/**
 * 
 */
UCLASS()
class FPS_DEMO_API UGamePlayUI : public UUserWidget
{
	GENERATED_BODY()

public:

	/*
		called to update number of bullets on magzine on runtime
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnMagazineStausChanged(int32 numOnMagzine , int32 MagzineSize);
	

	/*
		called to on shoot
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnShoot();

	/*
		called to update the ui about current focus
		used to update crosshair
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeFocus(bool newFocus);


	/*
		called when ever player gets close enogh to interactive actors like door
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractiveCase(bool bShowMessage, const FString &InteractiveMessage ,const FString &InteractiveKey);



};
