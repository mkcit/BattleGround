
#include "SoldierPlayerController.h"

void ASoldierPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShowWidgetOnScreen(GunWidget, GunWidgetClass, false);
}

void ASoldierPlayerController::RemoveAllWidgets()
{
	if (GunWidget) 
	{
		if (GunWidget->IsInViewport())
			GunWidget->RemoveFromViewport();
	}

}

void ASoldierPlayerController::ShowWidgetOnScreen(UUserWidget* Widget, TSubclassOf<UUserWidget> WidgetClass, bool SavePreviousWidget)
{
	if (!SavePreviousWidget)
		RemoveAllWidgets();

	Widget = CreateWidget(this, WidgetClass);
	if (Widget)
	{
		Widget->AddToViewport();
	}
}
