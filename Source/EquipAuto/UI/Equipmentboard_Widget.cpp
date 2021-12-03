// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipmentboard_Widget.h"

#include "Cell.h"
#include "Equipment.h"
#include "EquipmentBoard.h"
#include "EquipmentInfo.h"
#include "EquipmentUtility.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "EquipAutoInstance.h"


void UEquipmentboard_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	ResetBoard();
}

void UEquipmentboard_Widget::SetEquipmentboard(const UEquipmentBoard* Equipmentboard)
{
	if (EquipmentBoard == Equipmentboard)
	{
		return;
	}
	EquipmentBoard = Equipmentboard;
	
	ResetBoard();
	
	for (const auto& EquipmentInfoPair  : Equipmentboard->GetEquipments())
	{
		TArray<FCellInfo> MovedCells = EquipmentInfoPair.Value->GetMovedCells();
		for (const auto & Cell : MovedCells)
		{
			if (const UCell* CellWidget = Cast<UCell>(UGridPanel->GetChildAt(Cell.Point.X + Cell.Point.Y * 8)))
			{
				CellWidget->SetColor(EquipmentInfoPair.Value->Equipment->Color, Cell.ClosedSide);
			}
		}
	}
}

void UEquipmentboard_Widget::ResetBoard() const
{
	const FIntPoint BoardSize = FEquipmentUtility::GetGameInstance()->GetBoardSize();
	
	for (int32 i = 0; i < FEquipmentUtility::MaxBoardValidCellCount; ++i)
	{
		if (UCell* CellWidget = Cast<UCell>(UGridPanel->GetChildAt(i)))
		{
			CellWidget->ResetCell();
			const int32 X = i % FEquipmentUtility::MaxBoardColumn;
			const int32 Y = i / FEquipmentUtility::MaxBoardColumn;

			if (X >= BoardSize.X || Y >= BoardSize.Y)
			{
				CellWidget->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}
