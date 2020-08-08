// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierCharacter.h"

// Sets default values
ASoldierCharacter::ASoldierCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASoldierCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASoldierCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASoldierCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASoldierCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASoldierCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASoldierCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ASoldierCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("IncreaseMovementRate"), this, &ASoldierCharacter::IncreaseMovementRate);
	PlayerInputComponent->BindAxis(TEXT("DecreaseMovementRate"), this, &ASoldierCharacter::DecreaseMovementRate);

	PlayerInputComponent->BindAction(TEXT("ShowFirstPersonView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowFirstPersonView);
	PlayerInputComponent->BindAction(TEXT("ShowThirdPersonView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowThirdPersonView);
	PlayerInputComponent->BindAction(TEXT("ShowDownSightView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowDownSightView);
	PlayerInputComponent->BindAction(TEXT("ShowMissileView"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ShowMissileView);
	
	PlayerInputComponent->BindAction(TEXT("PullLeaveTrigger"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::PullTrigger);
	PlayerInputComponent->BindAction(TEXT("PullLeaveTrigger"), EInputEvent::IE_Released, this, &ASoldierCharacter::LeaveTrigger);
	PlayerInputComponent->BindAction(TEXT("ReloadArmory"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::ReloadArmory);
	
	PlayerInputComponent->BindAction(TEXT("PickUpWeapon"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::PickUpWeapon);
	PlayerInputComponent->BindAction(TEXT("LeaveWeapon"), EInputEvent::IE_Pressed, this, &ASoldierCharacter::LeaveWeapon);

	


}

void ASoldierCharacter::MoveForward(float AxisValue)
{
}

void ASoldierCharacter::MoveRight(float AxisValue)
{
}

void ASoldierCharacter::LookUp(float AxisValue)
{
}

void ASoldierCharacter::LookRight(float AxisValue)
{
}

void ASoldierCharacter::IncreaseMovementRate(float AxisValue)
{
}

void ASoldierCharacter::DecreaseMovementRate(float AxisValue)
{
}

void ASoldierCharacter::PickUpWeapon()
{
}

void ASoldierCharacter::LeaveWeapon()
{
}

void ASoldierCharacter::PullTrigger()
{
}

void ASoldierCharacter::LeaveTrigger()
{
}

void ASoldierCharacter::ReloadArmory()
{
}

// Called when the game starts or when spawned


void ASoldierCharacter::ShowFirstPersonView()
{
}

void ASoldierCharacter::ShowThirdPersonView()
{
}

void ASoldierCharacter::ShowDownSightView()
{
}

void ASoldierCharacter::ShowMissileView()
{
}

