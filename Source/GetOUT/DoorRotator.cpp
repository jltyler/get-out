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
}

// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll TriggerVolume0 PressurePlate
	if (PressurePlate->IsOverlappingActor(TriggerActor))
		OpenDoor();

	if (GetWorld()->GetTimeSeconds() - LastOpened > OpenTime)
		CloseDoor();


}

void UDoorRotator::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, -170.0f, 0.0f));
	LastOpened = GetWorld()->GetTimeSeconds();
}


void UDoorRotator::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
}

