// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "EquipmentBoard.h"
#include "Equipmentboard_Widget.h"
#include "EquipmentListElement.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ListView->OnItemSelectionChanged().AddUObject(this, &UHUDWidget::OnItemSelectionChanged);
	ListView->OnEntryWidgetGenerated().AddUObject(this, &UHUDWidget::OnEntryWidgetGenerated);
}

void UHUDWidget::AddEquipmentBoard(const TArray<UEquipmentBoard*>& EquipmentBoards) const
{
	ListView->SetListItems(EquipmentBoards);
	ListView->SetItemSelection(ListView->GetItemAt(0), true);
	TotalCount->SetText(FText::FromString(FString::Format(TEXT("총 개수:{0}"), {ListView->GetNumItems()})));
}

void UHUDWidget::AddEquipmentBoard(UEquipmentBoard* EquipmentBoard) const
{
	ListView->AddItem(EquipmentBoard);
	TotalCount->SetText(FText::FromString(FString::Format(TEXT("총 개수:{0}"), {ListView->GetNumItems()})));
}

void UHUDWidget::OnItemSelectionChanged(UObject* SelectedItem) const
{
	if (const UEquipmentBoard* Board = Cast<UEquipmentBoard>(SelectedItem))
	{
		Equipmentboard->SetEquipmentboard(Board);
	}
	else
	{
		Equipmentboard->ResetBoard();
	}
}

void UHUDWidget::OnEntryWidgetGenerated(UUserWidget& UserWidget) const
{
	UEquipmentBoard* SelectedBoard = ListView->GetSelectedItem<UEquipmentBoard>();
	UEquipmentListElement* ListElement = Cast<UEquipmentListElement>(&UserWidget);
	if (ListElement)
	{
		const auto EquipmentBoard = ListElement->GetListItem<UEquipmentBoard>();

		if (EquipmentBoard)
		{
			ListElement->NativeOnItemSelectionChanged(SelectedBoard == EquipmentBoard);	
		}
	}
}
