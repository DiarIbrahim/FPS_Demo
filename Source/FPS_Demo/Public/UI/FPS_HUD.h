// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_DEMO_API AFPS_HUD : public AHUD
{
	GENERATED_BODY()

	class UGamePlayUI* gameplayUI_ref;

protected:



	virtual void BeginPlay()override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Classes | UI")
	TSubclassOf<UUserWidget> gameplayUI_Class;
public:
	class UGamePlayUI* GetGamePlayUI();
	

	
};
