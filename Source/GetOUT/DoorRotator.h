// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorRotator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenDoor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseDoor);

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


private:
	bool AddMass(float Mass);

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION()
		float GetMassOfActor(AActor * OtherActor);
	UFUNCTION()
		void PlateBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void PlateEndOverlap(AActor* OverlappedActor, AActor* OtherActor);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OpenAngle = 90.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MassRequired = 200.0f;
	UPROPERTY(BlueprintReadOnly)
		float CurrentMass = 0.f;
	UPROPERTY(BlueprintReadWrite)
		FRotator OriginalRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ATriggerVolume * PressurePlate;
	UPROPERTY(BlueprintReadOnly)
		bool Open = false;
	UPROPERTY(BlueprintReadOnly)
		TArray<AActor *> OverlappingActors;
	UPROPERTY(BlueprintAssignable)
		FOnOpenDoor OnOpenDoor;
	UPROPERTY(BlueprintAssignable)
		FOnCloseDoor OnCloseDoor;
};
