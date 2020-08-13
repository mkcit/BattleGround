// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SoldierCharacter.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "SoldierAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEGROUND_API ASoldierAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float DeltaSeconds);


private:
	ASoldierCharacter* AISoldierCharacter = nullptr;

	FVector FirstLocation;
	FVector CurrentLocation;
};
