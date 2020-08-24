
#include "SoldierPlayerController.h"

void ASoldierPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShowWidgetOnScreen(GunWidget, GunWidgetClass, false);
}


UWidgetAnimation* ASoldierPlayerController::GetAnimationByName(FName AnimationName) const
{
    return nullptr;
}

UImage* ASoldierPlayerController::GetImageByName(FName ImageName) const
{
    UImage* const* WidgetImage = ImagesMap.Find(ImageName);

    if (WidgetImage != nullptr)
        return *WidgetImage;

    return nullptr;
}

UTextBlock* ASoldierPlayerController::GetTextBlockByName(FName TextBlockName) const
{
    UTextBlock* const* WidgetTextBlock = TextBlocksMap.Find(TextBlockName);

    if (WidgetTextBlock != nullptr)
        return *WidgetTextBlock;

    return nullptr;
}

void ASoldierPlayerController::ShowBulletsCountOnScreen(int32 CurrentBulletsCount, int32 CurrentBulletsCountInMagazine)
{
    UTextBlock* Text_MaxBulletsCount = GetTextBlockByName("Text_MaxBulletsCount");
    UTextBlock* Text_MaxCountBulletsInMagazine = GetTextBlockByName("Text_MaxCountBulletsInMagazine");
    
    if (Text_MaxCountBulletsInMagazine && Text_MaxBulletsCount)
    {
        Text_MaxBulletsCount->SetText(FText::AsNumber(CurrentBulletsCount));
        Text_MaxCountBulletsInMagazine->SetText(FText::AsNumber(CurrentBulletsCountInMagazine));
    }
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
        StoreObjectsInWidget(Widget);
	}
}

void ASoldierPlayerController::StoreObjectsInWidget(UUserWidget* Widget)
{
    AnimationsMap.Empty();
    ImagesMap.Empty();
    TextBlocksMap.Empty();

    if (Widget == nullptr)
        return;

    UProperty* Property = Widget->GetClass()->PropertyLink;
    while (Property != nullptr)
    {

        if (Property->GetClass() == UObjectProperty::StaticClass())
        {
            UObjectProperty* ObjProperty = Cast<UObjectProperty>(Property);


            // If Animation ?
            if (ObjProperty->PropertyClass == UWidgetAnimation::StaticClass())
            {

                UObject* Object = ObjProperty->GetObjectPropertyValue_InContainer(Widget);
                UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(Object);

                if (WidgetAnimation != nullptr && WidgetAnimation->MovieScene != nullptr)
                {
                    FName AnimationName = WidgetAnimation->MovieScene->GetFName();
                    AnimationsMap.Add(AnimationName, WidgetAnimation);
                }
            }
            else if (ObjProperty->PropertyClass == UImage::StaticClass())
            {

                UObject* Object = ObjProperty->GetObjectPropertyValue_InContainer(Widget);
                UImage* WidgetImage = Cast<UImage>(Object);

                if (WidgetImage != nullptr)
                {
                    FName ImageName = WidgetImage->GetFName();
                    ImagesMap.Add(ImageName, WidgetImage);
                }
            }
            else if (ObjProperty->PropertyClass == UTextBlock::StaticClass())
            {

                UObject* Object = ObjProperty->GetObjectPropertyValue_InContainer(Widget);
                UTextBlock* WidgetTextBlock = Cast<UTextBlock>(Object);

                if (WidgetTextBlock != nullptr)
                {
                    FName TextBlockName = WidgetTextBlock->GetFName();
                    TextBlocksMap.Add(TextBlockName, WidgetTextBlock);
                }
            }

        }
        Property = Property->PropertyLinkNext;
    }

}
