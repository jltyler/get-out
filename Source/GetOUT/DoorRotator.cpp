// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorRotator.h"
#include "GameFramework/Actor.h"


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

	auto OwningActor = GetOwner();
	auto ActorRotation = OwningActor->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("%s has rotation of %s"), *OwningActor->GetName(), *ActorRotation.ToString())
	ActorRotation = ActorRotation.Add(-30.0f, -40.0f, 0.0f);
	UE_LOG(LogTemp, Warning, TEXT("%s has rotation of %s"), *OwningActor->GetName(), *ActorRotation.ToString())
	OwningActor->SetActorRotation(ActorRotation);
}


// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

