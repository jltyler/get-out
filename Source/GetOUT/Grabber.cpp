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
	PhysHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysHandle) UE_LOG(LogTemp, Error, TEXT("%s.PhysHandle is NULL"), *Owner->GetName());

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


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysHandle->GetGrabbedComponent())
	{
		FVector TraceStartPoint;
		FRotator ViewRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(TraceStartPoint, ViewRotation);
		FVector TraceEndPoint(TraceStartPoint + ViewRotation.Vector() * Reach);
		PhysHandle->SetTargetLocation(TraceEndPoint);
	}
}

void UGrabber::Yaw(float Diff)
{
	UE_LOG(LogTemp, Log, TEXT("Yaw: %f"), Diff);
}

// Release Grabbed Object
inline void UGrabber::Release()
{
	PhysHandle->ReleaseComponent();
}

// Grab object
void UGrabber::Grab()
{
	FVector TraceStartPoint;
	FRotator ViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(TraceStartPoint, ViewRotation);
	FVector TraceEndPoint(TraceStartPoint + ViewRotation.Vector() * Reach);

	FHitResult TraceHit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner);
	bool Hit = World->LineTraceSingleByChannel(TraceHit, TraceStartPoint, TraceEndPoint, ECC_PhysicsBody, QueryParams);
	DrawDebugLine(World, TraceStartPoint, TraceEndPoint, (Hit ? FColor(0, 220, 0) : FColor(230, 0, 0)), true, 1.0f, 0, 5.0f);
	if (Hit)
	{
		PhysHandle->GrabComponent(TraceHit.GetComponent(), TraceHit.BoneName, TraceEndPoint, false);
	}

}
