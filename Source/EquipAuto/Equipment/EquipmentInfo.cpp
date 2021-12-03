#include "EquipmentInfo.h"

#include "EquipmentUtility.h"

FEquipmentInfo::FEquipmentInfo(const TSharedPtr<FEquipment>& Equipment, int32 Position)
	: Equipment(Equipment),
	  Position(Position)
{
}

TArray<FCellInfo> FEquipmentInfo::GetMovedCells() const
{
	TArray<FCellInfo> MovedCells;

	for (const auto & Cell : Equipment->Cells)
	{
		MovedCells.Emplace(FCellInfo { Cell.ClosedSide, FIntPoint { Cell.Point.X + Position % FEquipmentUtility::MaxBoardColumn, Cell.Point.Y + Position / FEquipmentUtility::MaxBoardColumn }});
	}
	
	return MoveTemp(MovedCells);
}
