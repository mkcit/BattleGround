// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairHUD.h"

void ACrosshairHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ACrosshairHUD::DrawHUD()
{
	// If Gun is Picked by Soldier
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		ASoldierCharacter* SoldierCharacter = Cast<ASoldierCharacter>(PlayerController->GetPawn());
		if (SoldierCharacter)
		{
			GunActor = SoldierCharacter->GetGunActor();
			if (GunActor)
			{
				FVector2D ScreenLocation = GunActor->GetScreenLocation();

				//Right
				float W = Width;
				float H = Height;
				float X = ScreenLocation.X - W - 5;
				float Y = ScreenLocation.Y - H / 2;
				DrawRect(FLinearColor::Red, X, Y, W, H);
				//Left
				W = Width;
				H = Height;
				X = ScreenLocation.X + 5;
				Y = ScreenLocation.Y - H / 2;
				DrawRect(FLinearColor::Red, X, Y, W, H);
				//Up
				W = Height;
				H = Width;
				X = ScreenLocation.X - W / 2;
				Y = ScreenLocation.Y - H - 5;
				DrawRect(FLinearColor::Red, X, Y, W, H);
				//Down
				W = Height;
				H = Width;
				X = ScreenLocation.X - W / 2;
				Y = ScreenLocation.Y + 5;
				DrawRect(FLinearColor::Red, X, Y, W, H);
			}
		}
	}
	
}