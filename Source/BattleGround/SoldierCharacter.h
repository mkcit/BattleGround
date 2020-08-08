// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	void PullTrigger();
	void LeaveTrigger();
	void ReloadArmory();

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


	UPROPERTY(EditAnywhere, Category = "Setup")
	float CharacterMovementSpeedRate = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float CharacterRotationSpeedRate = 9.f;
};
