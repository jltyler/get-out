// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"


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
	World = GetWorld();
	SetupPhysHandle();
	SetupInput();
}

void UGrabber::SetupInput()
{
	Input = Owner->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Input->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		Input->BindAxis("View X", this, &UGrabber::Yaw);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("%s.Input is NULL"), *Owner->GetName());
}

void UGrabber::SetupPhysHandle()
{
	PhysHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysHandle) UE_LOG(LogTemp, Error, TEXT("%s.PhysHandle is NULL"), *Owner->GetName());
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysHandle && PhysHandle->GetGrabbedComponent())
	{
		PhysHandle->SetTargetLocation(GetReachEnd());
	}
}

inline FVector UGrabber::GetViewLocation()
{
	FRotator ViewRotation;
	return GetViewLocationAndRotation(ViewRotation);
}

FVector UGrabber::GetViewLocationAndRotation(FRotator & out_ViewRotation)
{
	FVector ViewLocation;
	World->GetFirstPlayerController()->GetPlayerViewPoint(ViewLocation, out_ViewRotation);
	return ViewLocation;
}

FVector UGrabber::GetReachEnd()
{
	FRotator ViewRotation;
	FVector ViewLocation(GetViewLocationAndRotation(ViewRotation));
	return ViewLocation + ViewRotation.Vector() * Reach;
}

void UGrabber::Grab()
{
	if (!PhysHandle) return;
	FHitResult TraceHit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	if (World->LineTraceSingleByChannel(TraceHit, GetViewLocation(), GetReachEnd(), ECC_PhysicsBody, QueryParams))
	{
		PhysHandle->GrabComponent(TraceHit.GetComponent(), TraceHit.BoneName, TraceHit.Location, true);
	}
}

inline void UGrabber::Release()
{
	if (!PhysHandle) return;
	PhysHandle->ReleaseComponent();
}

void UGrabber::Yaw(float Diff)
{
	return;
}
