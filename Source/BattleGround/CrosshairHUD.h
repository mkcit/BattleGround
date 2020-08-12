// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SoldierCharacter.h"
#include "GunActor.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrosshairHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEGROUND_API ACrosshairHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay();
	virtual void DrawHUD();

private:
	AGunActor* GunActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float Width = 8;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float Height = 4;

};
