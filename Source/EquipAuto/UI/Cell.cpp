// Fill out your copyright notice in the Description page of Project Settings.


#include "Cell.h"

#include "ECellClosedSide.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"

void UCell::NativeConstruct()
{
	Super::NativeConstruct();

	Image = Cast<UImage>(GetWidgetFromName(TEXT("Image_116")));
	check(Image);

	ImageOverlaySlot = Cast<UOverlaySlot>(Image->Slot);
	check(ImageOverlaySlot.Get());
}

void UCell::SetColor(FColor Color, ECellClosedSide ClosedSide) const
{
	Image->SetVisibility(ESlateVisibility::Visible);
	Image->SetColorAndOpacity(Color);

	FMargin Margin { ImagePadding };
	
	if (EnumHasAnyFlags(ClosedSide, ECellClosedSide::Bottom))
	{
		Margin.Bottom = 0;
	}

	if (EnumHasAnyFlags(ClosedSide, ECellClosedSide::Top))
	{
		Margin.Top = 0;
	}

	if (EnumHasAnyFlags(ClosedSide, ECellClosedSide::Right))
	{
		Margin.Right = 0;
	}

	if (EnumHasAnyFlags(ClosedSide, ECellClosedSide::Left))
	{
		Margin.Left = 0;
	}

	ImageOverlaySlot->SetPadding(Margin);
}

void UCell::ResetCell() const
{
	Image->SetVisibility(ESlateVisibility::Collapsed);
}
