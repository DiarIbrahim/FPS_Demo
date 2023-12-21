// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"
#include "Actors/Door.h"
#include "Player/FPS_Player.h"
#include "UI/GamePlayUI.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SphereRadius = 50;
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionProfileName("OverlapAll");

	OnComponentBeginOverlap.AddDynamic(this , &UInteractComponent::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UInteractComponent::OnOverlapEnd);


}

// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADoor>(OtherActor)) {
		CurrentInteractiveOverlap = Cast<ADoor>(OtherActor);
		OnInteractiveOverlapped();
	}
}

void UInteractComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ADoor>(OtherActor) == CurrentInteractiveOverlap) {
		CurrentInteractiveOverlap =  nullptr;
		OnNoInteractive();
	}

}

void UInteractComponent::OnInteractiveOverlapped()
{
	if (GetPlayer() && GetPlayer()->GetGamePlayUI()) {
		GetPlayer()->GetGamePlayUI()->OnInteractiveCase(1, CurrentInteractiveOverlap->bIsOpen? "Clase Door" : "Open Door", "F");
	}
}

void UInteractComponent::OnNoInteractive()
{
	if (GetPlayer() && GetPlayer()->GetGamePlayUI()) {
		GetPlayer()->GetGamePlayUI()->OnInteractiveCase(0, "","");
	}
}

AFPS_Player* UInteractComponent::GetPlayer()
{
	return Cast<AFPS_Player>(GetOwner());

}

void UInteractComponent::Excute_Interact()
{
	if (CurrentInteractiveOverlap) {
		CurrentInteractiveOverlap->Interact();
	}
}

void UInteractComponent::Start_Interact()
{
	if (CurrentInteractiveOverlap && AnimMontage_Interact) {
		GetPlayer()->PlayAnimMontage(AnimMontage_Interact);
	}
}
