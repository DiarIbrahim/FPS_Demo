// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPS_Player.generated.h"

UCLASS()
class FPS_DEMO_API AFPS_Player : public ACharacter
{
	GENERATED_BODY()

private:

	/*	 INPUT FUNCTIONS		*/

	void Mouse_X(float v);
	void Mouse_Y(float v);

	void Forward_backward(float v);
	void right_left(float v);

	void shift_down();
	void shift_Up();


	void rightMouse_down();
	void rightMouse_Up();



	void HundleInputs();

protected:
	/*		Variables		*/

	/*
		is shift keep hold
	*/ 
	bool bShift = false;
	
	/*
		is right mouse button keep hold
	*/
	bool bRightMouseButton = false;
	
	/*
		character velocity in forward-backward directions
	*/
	float forwardVelocity = 0;
	/*
		character velocity in right-left direcion
	*/
	float rightLeftVelocity = 0;

	/*
		rotation sway amount for right-left movement
	*/
	UPROPERTY(BlueprintReadWrite , EditAnywhere , Category = "Variables | Movement")
	float movementSwayRightLeft = 7;
	/*
		rotation sway amount for backward movement
		it is negative cause it is backward
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Variables | Movement")
	float movementSwaybackward= -5;
	/*
		movement sway speed multiplayer
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Variables | Movement")
	float MovementSwaySpeedMul = 1;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Components

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UCameraComponent* camera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USpringArmComponent* CameraBoom;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USpringArmComponent* sway;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UWeaponManagerComponent* Weapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInteractComponent* InteractComponent;


	/*
		rotates the FPS mesh slitly tward the movement direction
	*/
	void MovmentSway(float DeltaTime);

	/*
		hundle aming
		places the weapon in  a proper position for aiming
	*/
	void HundleAiming(float DeltaTime);



public:
	// Sets default values for this character's properties
	AFPS_Player();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	/*
		returns an index represents the current animation state
		returns 0 if speed is 0.0        (idle)
		returns 1 if speed is ~600       (walk)
		returns 2 if speed more than 600 (run)
	*/

	short GetSpeedIndex() const;
	
	/*
		calculates velocity  starting from -1 to 1
		for right and left

	*/
	void CalculateVelocity();

	/*
		called while shooting
	*/
	UFUNCTION(BlueprintImplementableEvent, Meta = (displayName = "OnShoot"))
	void OnShoot_BP();
	
	/*
		returns weapon manager component
	*/
	UFUNCTION(BlueprintCallable)
	class UWeaponManagerComponent* GetWeapon() const { return Weapon; }
	class UCameraComponent* GetCamera()const { return camera; }

	bool IsRunning()const;
	bool IsAiming()const;



	class UGamePlayUI* GetGamePlayUI();

};
