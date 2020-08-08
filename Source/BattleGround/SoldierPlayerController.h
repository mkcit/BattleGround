// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SoldierPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEGROUND_API ASoldierPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void RemoveAllWidgets();

	void ShowWidgetOnScreen(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, bool SavePreviousWidget);


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GunWidgetClass;

	UUserWidget* GunWidget = nullptr;


	
};
