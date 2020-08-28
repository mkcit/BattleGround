// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Image.h"
#include "Components/TextBlock.h"
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


public:
	void ShowGunWidget();
	void ShowLauncherMissileSystemWidget();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;
	UImage* GetImageByName(FName ImageName) const;
	UTextBlock* GetTextBlockByName(FName TextBlockName) const;

	void ShowBulletsCountOnScreen(int32 CurrentBulletsCount, int32 CurrentBulletsCountInMagazine);

protected:
	virtual void BeginPlay() override;

	

private:
	void ShowWidgetOnScreen(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, bool SavePreviousWidget); 
	void StoreObjectsInWidget(UUserWidget* Widget);


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GunWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LauncherMissileSystemWidgetClass;

	TMap<FName, UImage*> ImagesMap;
	TMap<FName, UWidgetAnimation*> AnimationsMap;
	TMap<FName, UTextBlock*> TextBlocksMap;

	UUserWidget* GunWidget = nullptr;
	UUserWidget* LauncherMissileSystemWidget = nullptr;
};
