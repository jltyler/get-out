// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorRotator.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Public/TimerManager.h"


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

	OriginalRotation = Owner->GetActorRotation();
	if (PressurePlate)
	{
		PressurePlate->OnActorBeginOverlap.AddDynamic(this, &UDoorRotator::PlateBeginOverlap);
		PressurePlate->OnActorEndOverlap.AddDynamic(this, &UDoorRotator::PlateEndOverlap);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("PressurePlate is NULL!"))
}

bool UDoorRotator::AddMass(float Mass)
{
	CurrentMass += Mass;
	if (CurrentMass >= MassRequired)
	{
		OpenDoor();
		return true;
	}
	else
	{
		BeginCloseDoor();
		return false;
	}
}

float UDoorRotator::GetMassOfActor(AActor * OtherActor)
{
	TArray<UStaticMeshComponent *> MeshComponents;
	OtherActor->GetComponents<UStaticMeshComponent>(MeshComponents);
	float Mass = 0.f;
	for (auto CurrMesh : MeshComponents)
	{
		Mass += CurrMesh->GetMass();
	}
	return Mass;
}

void UDoorRotator::PlateBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("PlateBeginOverlap()"));
		//OtherActor->GetComponentByClass<UStaticMeshComponent>
	OverlappingActors.Add(OtherActor);
	AddMass(GetMassOfActor(OtherActor));
}

void UDoorRotator::PlateEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("PlateEndOverlap()"));
		//OtherActor->GetComponentByClass<UStaticMeshComponent>
	OverlappingActors.Remove(OtherActor);
	AddMass(-GetMassOfActor(OtherActor));
}

// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDoorRotator::OpenDoor()
{
	if (Open) return;
	Owner->SetActorRotation(FRotator(0.0f, OriginalRotation.Yaw + OpenAngle, 0.0f));
	Open = true;
}

void UDoorRotator::BeginCloseDoor()
{
	if (!Open) return;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDoorRotator::CloseDoor, OpenTime, false, OpenTime);
}

void UDoorRotator::CloseDoor()
{
	if (!Open) return;
	Owner->SetActorRotation(OriginalRotation);
	Open = false;
}

