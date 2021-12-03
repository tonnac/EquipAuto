// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentListElement.h"

#include "EquipAutoInstance.h"
#include "EquipmentBoard.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

void UEquipmentListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	if (UEquipmentBoard* Board = Cast<UEquipmentBoard>(ListItemObject))
	{
		this->EquipmentBoard = Board;
		
		Count->SetText(FText::AsNumber(Board->GetCountEquipments()));
		TotalStat->SetText(FText::AsNumber(Board->GetTotalStat()));

		NativeOnItemSelectionChanged(false);
	}
}

void UEquipmentListElement::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	UBorder* Border = Cast<UBorder>(GetRootWidget());
	
	if (Border)
	{
		if (bIsSelected)
		{
			Border->SetBrushColor(SelectColor);
		}
		else
		{
			Border->SetBrushColor(FLinearColor{1.f,1.f,1.f,0.f });
		}
	}
}

bool UEquipmentListElement::IsListItemSelectable() const
{
	return true;
}
