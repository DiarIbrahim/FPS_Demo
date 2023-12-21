// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FPS_HUD.h"
#include "UI/GamePlayUI.h"

void AFPS_HUD::BeginPlay()
{
	// first spawn
	GetGamePlayUI();
}

UGamePlayUI* AFPS_HUD::GetGamePlayUI()
{
	if(gameplayUI_ref) return gameplayUI_ref;

	if (!gameplayUI_Class) return nullptr;

	gameplayUI_ref = Cast<UGamePlayUI>(CreateWidget(GetWorld(), gameplayUI_Class));
	if (gameplayUI_ref) {
		gameplayUI_ref->AddToViewport();
		return gameplayUI_ref;
	}

	return nullptr;

}
