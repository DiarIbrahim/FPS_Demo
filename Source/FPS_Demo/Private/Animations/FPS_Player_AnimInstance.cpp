// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/FPS_Player_AnimInstance.h"
#include "Player/FPS_Player.h"

void UFPS_Player_AnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (GetPlayer()) {
		CharacterSpeedIndex = GetPlayer()->GetSpeedIndex();
	}

}

AFPS_Player* UFPS_Player_AnimInstance::GetPlayer() const
{
	return Cast<AFPS_Player>(GetOwningActor());
}
