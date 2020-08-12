// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/Image.h"
#include "GunActor.h"
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
	void ReloadGunMagazine();
	void Crouch();

	AGunActor* GetGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	

	UFUNCTION(BlueprintPure)
	float GetSoldierCharacterSpeed();

	UFUNCTION(BlueprintPure)
	float GetSoldierCharacterAngle();

	UFUNCTION(BlueprintPure)
	FRotator GetBoneRotation() const;

	UFUNCTION(BlueprintPure)
	bool GetIfSoldierCharacterIsCrouchingNow();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AGunActor> GunActorClass;

	UPROPERTY()
	AGunActor* GunActor = nullptr;


	void ShowFirstPersonView();
	void ShowThirdPersonView();
	void ShowDownSightView();
	void ShowMissileView();

	void StoreCameras();
	void DeActivateAllCameras(); 
	void CalculateTheAngle();
	float* GetSpeedFactor();

	bool IsIncreasingCharacterMovementSpeedRate = false;
	bool IsDecreasingCharacterMovementSpeedRate = false;
	bool IsSoldierCharacterCrouchingNow = false;


	UPROPERTY(EditAnywhere, Category = "Setup")
	float DefaultCharacterMovementSpeedRate = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float DefaultCharacterRotationSpeedRate = 9.f;

	float CharacterMovementSpeedRate;
	float BoneRotatonAngle;

	UFUNCTION(BlueprintPure)
	FVector2D GetScreenPosition();

	UCameraComponent* const* FirstPersonViewCamera = nullptr;
	UCameraComponent* const* ThirdPersonViewCamera = nullptr;
	UCameraComponent* const* DownSightViewCamera = nullptr;
	TMap<FName, UCameraComponent*> Cameras;

	UImage* Image_Up = nullptr;
	UImage* Image_Down = nullptr;
	UImage* Image_Right = nullptr;
	UImage* Image_Left = nullptr;

	FVector2D ScreenLocation;
};
