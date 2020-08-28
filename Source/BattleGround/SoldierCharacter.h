// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "KornetSystemActor.h"
#include "SoldierPlayerController.h"
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
	void StopReloadingMagazine();
	void Crouch();
	void FireGun();

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

	UFUNCTION(BlueprintPure)
	bool GetIfSoldierCharacterIsReloadingNow();

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
	void ShowBulletsCountOnScreen();
	float* GetSpeedFactor();

	bool IsIncreasingCharacterMovementSpeedRate = false;
	bool IsDecreasingCharacterMovementSpeedRate = false;
	bool IsSoldierCharacterCrouchingNow = false;
	bool IsAutoGunTriggerPulled = false;
	bool ReloadingMagazineNow = false;
	bool IsSoldierInGunArea = false;
	bool CanControlOverlappingActor = false;


	float CurrentSecond = 0.f;
	float LastSecond = 0.f;


	UPROPERTY(EditAnywhere, Category = "Setup")
	float DefaultCharacterMovementSpeedRate = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float DefaultCharacterRotationSpeedRate = 9.f;


	UFUNCTION(BlueprintPure)
	FVector2D GetScreenPosition();

	UCameraComponent* const* FirstPersonViewCamera = nullptr;
	UCameraComponent* const* ThirdPersonViewCamera = nullptr;
	UCameraComponent* const* DownSightViewCamera = nullptr;
	TMap<FName, UCameraComponent*> Cameras;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<UCameraShake> CameraShakeClass;

	ASoldierPlayerController* PlayerController = nullptr;
	FVector2D ScreenLocation;


	float CharacterMovementSpeedRate;
	float BoneRotatonAngle;

	int32 CurrentBulletsCount;
	int32 CurrentBulletsCountInMagazine;

	UPrimitiveComponent* PrimitiveOverlappingComponent = nullptr; 
	AKornetSystemActor* KornetSystemActor = nullptr;
};
