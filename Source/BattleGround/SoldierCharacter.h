// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoldierCharacter.generated.h"

UCLASS()
class BATTLEGROUND_API ASoldierCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoldierCharacter();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void IncreaseMovementRate(float AxisValue);
	void DecreaseMovementRate(float AxisValue);

	void PickUpWeapon();
	void LeaveWeapon();

	void PullTrigger();
	void LeaveTrigger();
	void ReloadArmory();

	UFUNCTION(BlueprintPure)
	float GetCharacterSpeed();

	UFUNCTION(BlueprintPure)
	float GetCharacterAngle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void ShowFirstPersonView();
	void ShowThirdPersonView();
	void ShowDownSightView();
	void ShowMissileView();

	void StoreCameras();
	void DeActivateAllCameras();

	bool IsIncreasingCharacterMovementSpeedRate = false;
	bool IsDecreasingCharacterMovementSpeedRate = false;


	UPROPERTY(EditAnywhere, Category = "Setup")
	float CharacterMovementSpeedRate = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float CharacterRotationSpeedRate = 9.f;

	UCameraComponent* const* FirstPersonViewCamera = nullptr;
	UCameraComponent* const* ThirdPersonViewCamera = nullptr;
	UCameraComponent* const* DownSightCamera = nullptr;
	TMap<FName, UCameraComponent*> Cameras;
};
