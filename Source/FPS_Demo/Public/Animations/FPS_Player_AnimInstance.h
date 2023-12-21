// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPS_Player_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_DEMO_API UFPS_Player_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	/*
		0 = idle
		1 = walk
		2 = run
	*/
	UPROPERTY(BlueprintReadOnly)
	float  CharacterSpeedIndex = 0;
	
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	class AFPS_Player* GetPlayer()const;

};
