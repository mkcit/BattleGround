// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"

void ASoldierAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPawn())
	{
		AISoldierCharacter = Cast<ASoldierCharacter>(GetPawn());
		FirstLocation = AISoldierCharacter->GetActorLocation();
	}
}

void ASoldierAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AISoldierCharacter)
	{

		CurrentLocation = AISoldierCharacter->GetActorLocation();
		float Distance = FVector::Dist(FirstLocation, CurrentLocation);

		float MoveForward = 0;
		float MoveRight = 0;
		float IncreaseMovementRate = 0;

		if (Distance < 2700)
		{
			MoveForward = 1;
			if (Distance > 500) // 5m = 5 * 100 = 1500 c.m
			{
				IncreaseMovementRate = 1;
			}
			if (Distance > 2500) // 5m = 5 * 100 = 1500 c.m
			{
				IncreaseMovementRate = 0;
				MoveForward = 0;
				MoveRight = 1;
				AISoldierCharacter->PullTrigger();
			}
		}
		else
		{
			IncreaseMovementRate = 0;
			MoveRight = 0;
			MoveForward = 0;
		}
		AISoldierCharacter->IncreaseMovementRate(IncreaseMovementRate);
		AISoldierCharacter->MoveRight(MoveRight);
		AISoldierCharacter->MoveForward(MoveForward);

	}
}
