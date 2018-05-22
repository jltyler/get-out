// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GETOUT_API UDoorRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume * PressurePlate;
		float LastOpened = 0.0f;
	UPROPERTY(EditAnywhere)
		float OpenTime = 1.0f;
	AActor * TriggerActor;
	AActor * Owner;
	bool Opened = false;
	FRotator OriginalRotation;
};
