// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorRotator.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UDoorRotator::UDoorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorRotator::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	TriggerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	OriginalRotation = Owner->GetActorRotation();
}

// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll TriggerVolume PressurePlate
	if (PressurePlate->IsOverlappingActor(TriggerActor))
		OpenDoor();

	if (Opened && GetWorld()->GetTimeSeconds() - LastOpened > OpenTime)
		CloseDoor();


}

void UDoorRotator::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OriginalRotation.Yaw + OpenAngle, 0.0f));
	LastOpened = GetWorld()->GetTimeSeconds();
	Opened = true;
}


void UDoorRotator::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OriginalRotation.Yaw, 0.0f));
	Opened = false;
}

