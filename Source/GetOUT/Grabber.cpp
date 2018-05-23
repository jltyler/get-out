// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point
	FVector ViewLocation;
	FRotator ViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	//Owner->GetActorEyesViewPoint(ViewLocation, ViewRotation);
	UE_LOG(LogTemp, Warning, TEXT("Player ViewLocation: %s | ViewRotation: %s"), *ViewLocation.ToString(), *ViewRotation.ToString())
	// Raycast to reach distance
	FHitResult TraceHit;
	FCollisionObjectQueryParams ObjectParams(ECC_PhysicsBody);
	FVector TraceEndPoint(ViewLocation + ViewRotation.Vector() * Reach);
	UE_LOG(LogTemp, Warning, TEXT("Trace End: %s"), *TraceEndPoint.ToString())
	if (GetWorld()->LineTraceSingleByObjectType(TraceHit, ViewLocation, TraceEndPoint, ObjectParams))
		UE_LOG(LogTemp, Warning, TEXT("Trace says Yay!"))
	// If correct object is hit
		// Grab object
}

