// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPS_Player.h"
#include "Camera/CameraComponent.h"
#include "gameframework/springarmComponent.h"
#include "gameframework/CharacterMovementComponent.h"
#include "FPS_Demo/FPS_Demo.h"
#include "UI/FPS_HUD.h"
#include "UI/GamePlayUI.h"
#include "Components/WeaponManagerComponent.h"
#include "Components/InteractComponent.h"






// Sets default values
AFPS_Player::AFPS_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	if (GetCharacterMovement()) {
		GetCharacterMovement()->MaxWalkSpeed = 300;
	}

	if (!InteractComponent) {
		InteractComponent = CreateDefaultSubobject<UInteractComponent>(FName("Interact Component"));
		InteractComponent->SetupAttachment(GetRootComponent());
	}

	if (!Weapon) {
		Weapon = CreateDefaultSubobject<UWeaponManagerComponent>(FName("Weapon"));
	}


	if (!CameraBoom) {
		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("Camera boom"));
		CameraBoom->SetupAttachment(GetRootComponent());
		CameraBoom->bUsePawnControlRotation = true;
		CameraBoom->TargetArmLength = 0;
	}


	if (!camera) {
		camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
		camera->SetupAttachment(CameraBoom);
	}

	if (!sway) {
		sway= CreateDefaultSubobject<USpringArmComponent>(FName("fps hand sway"));
		sway->SetupAttachment(camera);
		sway->bUsePawnControlRotation = false;
		sway->TargetArmLength = 0;
		sway->bEnableCameraLag = true;
		sway->bEnableCameraRotationLag = true;

	}


	GetMesh()->SetupAttachment(sway);


}



// Called when the game starts or when spawned
void AFPS_Player::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* pc = Cast<APlayerController>(GetController())) {
		pc->PlayerCameraManager->ViewPitchMax = 65;
		pc->PlayerCameraManager->ViewPitchMin = -75;
	}

}

bool bReportRunningStarted = false;
bool bReportRunningEnded   = false;

void AFPS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CalculateVelocity();

	MovmentSway(DeltaTime);
	
	HundleInputs();

	HundleAiming(DeltaTime);



	if (IsRunning() && !bReportRunningStarted) {
		bReportRunningStarted = true;
		bReportRunningEnded = false;
		if (GetGamePlayUI()) {
			GetGamePlayUI()->OnChangeFocus(0);
		}
	}
	else if (!IsRunning() && !bReportRunningEnded) {
		bReportRunningStarted = false;
		bReportRunningEnded = true;
		if (GetGamePlayUI()) {
			GetGamePlayUI()->OnChangeFocus(1);
		}
	}


}

void AFPS_Player::HundleInputs()
{
	
	if (bShift && !bRightMouseButton && forwardVelocity > 0.5 ) {
		GetCharacterMovement()->MaxWalkSpeed = 500;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 300;
	}
}



#pragma region INPUT



void AFPS_Player::Mouse_X(float v)
{
	AddControllerYawInput(v);
}

void AFPS_Player::Mouse_Y(float v)
{
	AddControllerPitchInput(-v);
}

void AFPS_Player::Forward_backward(float v)
{
	AddMovementInput(GetActorForwardVector() , v);
}

void AFPS_Player::right_left(float v)
{
	AddMovementInput(GetActorRightVector(), v);
}

void AFPS_Player::shift_down()
{
	bShift = true;
}

void AFPS_Player::shift_Up()
{
	bShift = false;
}

void AFPS_Player::rightMouse_down()
{
	bRightMouseButton = true;
}

void AFPS_Player::rightMouse_Up()
{
	bRightMouseButton = false;
}





// Called to bind functionality to input
void AFPS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Mouse X", this, &AFPS_Player::Mouse_X);
	PlayerInputComponent->BindAxis("Mouse Y", this, &AFPS_Player::Mouse_Y);

	PlayerInputComponent->BindAxis("forward_backward", this, &AFPS_Player::Forward_backward);
	PlayerInputComponent->BindAxis("right_left", this, &AFPS_Player::right_left);

	PlayerInputComponent->BindAction("shift", EInputEvent::IE_Pressed,this, &AFPS_Player::shift_down);
	PlayerInputComponent->BindAction("shift", EInputEvent::IE_Released, this, &AFPS_Player::shift_Up);

	PlayerInputComponent->BindAction("rightMouse", EInputEvent::IE_Pressed, this, &AFPS_Player::rightMouse_down);
	PlayerInputComponent->BindAction("rightMouse", EInputEvent::IE_Released, this, &AFPS_Player::rightMouse_Up);


	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, Weapon, &UWeaponManagerComponent::Shoot_Start);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Released, Weapon, &UWeaponManagerComponent::Shoot_End);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, Weapon, &UWeaponManagerComponent::Reload);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, InteractComponent, &UInteractComponent::Start_Interact);



}


#pragma endregion


float rollSway  = -1 ;
float pitchSway = -1 ;

void AFPS_Player::MovmentSway(float DeltaTime)
{


	// check if the character is stopped and the movment sway reseted

	if (
		(rightLeftVelocity == 0.0 && FMath::IsNearlyEqual(GetMesh()->GetRelativeRotation().Roll ,0 , 0.005))
		&&
		(forwardVelocity == 0.0 && FMath::IsNearlyEqual(GetMesh()->GetRelativeRotation().Pitch ,0,0.005))

		) 
	{
		return;	
	}

	if (GetMesh()) {
		
		rollSway  = FMath::Lerp(rollSway  , (IsAiming() ? 0.3 : 1) * movementSwayRightLeft * rightLeftVelocity					 ,  10 * MovementSwaySpeedMul * DeltaTime);
		pitchSway = FMath::Lerp(pitchSway , (IsAiming() ? 0.3 : 1) * movementSwaybackward  * FMath::Clamp(forwardVelocity , -1,0) , 10 * MovementSwaySpeedMul * DeltaTime);

		GetMesh()->SetRelativeRotation(FRotator(pitchSway,GetMesh()->GetRelativeRotation().Yaw, rollSway));
	}


}

float blendMeshLoc = 0;
float blendMeshLoc_local = 0;

void AFPS_Player::HundleAiming(float DeltaTime)
{
	if (!Weapon || !camera) return;

	if ( (!IsAiming() && FMath::IsNearlyEqual(blendMeshLoc,0 , 0.001))  || (IsAiming() && FMath::IsNearlyEqual(blendMeshLoc, 1,0.001)) ) return;


	FVector AimBoneLocation = GetMesh()->GetBoneLocation(Weapon->AimSocketName);

	FVector AimPos = camera->GetComponentLocation() + camera->GetForwardVector() * Weapon->AimOffset.X + 
													  camera->GetRightVector()* Weapon->AimOffset.Y +
													  camera->GetUpVector() * Weapon->AimOffset.Z;

	FVector difference = AimPos - AimBoneLocation;


	blendMeshLoc = FMath::Lerp(blendMeshLoc, IsAiming() ? 1 : 0, DeltaTime * 10);
	blendMeshLoc_local = FMath::Lerp(blendMeshLoc_local, IsAiming() ? 0 : 1, DeltaTime * 10);


	if (IsAiming()) {
		GetMesh()->SetWorldLocation(FMath::Lerp(GetMesh()->GetComponentLocation(), GetMesh()->GetComponentLocation() + difference, blendMeshLoc));
	}
	else {
		GetMesh()->SetRelativeLocation(FMath::Lerp(GetMesh()->GetRelativeLocation(), FVector::Zero(), blendMeshLoc_local));
	}
	
	if (APlayerController* pc = Cast<APlayerController>(GetController())) {
		pc->PlayerCameraManager->SetFOV(FMath::Lerp(90, 70, blendMeshLoc));
	}

}


short AFPS_Player::GetSpeedIndex() const
{
	float speed = GetCharacterMovement()->Velocity.Length();
	if (speed == .0)
		return 0;
	else if (IsRunning())
		return 2;
	else return 1;
}

void AFPS_Player::CalculateVelocity()
{
	if (!GetCharacterMovement()) return;

	if (GetCharacterMovement()->Velocity.Length() == 0.0) {
		forwardVelocity = 0.0;
		rightLeftVelocity = 0.0;
	}

	FVector velocityVector = GetCharacterMovement()->Velocity;
	velocityVector.Normalize();

	forwardVelocity = FVector::DotProduct(GetActorForwardVector() , velocityVector);
	rightLeftVelocity = FVector::DotProduct(GetActorRightVector() , velocityVector);
}

bool AFPS_Player::IsRunning() const
{
	return GetCharacterMovement()->Velocity.Length() >= 320 && !Weapon->IsReloading();
}

bool AFPS_Player::IsAiming() const
{
	return bRightMouseButton && !Weapon->IsReloading();
}

UGamePlayUI* AFPS_Player::GetGamePlayUI()
{
	if (Cast<APlayerController>(GetController()) && Cast<APlayerController>(GetController())->GetHUD()) {
		return Cast<AFPS_HUD>(Cast<APlayerController>(GetController())->GetHUD())->GetGamePlayUI();
	} else return nullptr;
}

