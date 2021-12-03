#include "Equipment.h"

#include "ECellClosedSide.h"
#include "EquipmentUtility.h"
#include "Core/EquipAutoInstance.h"

FCellInfo::FCellInfo()
	: ClosedSide(ECellClosedSide::None)
{
}

FCellInfo::FCellInfo(const FIntPoint& Point)
	: ClosedSide(ECellClosedSide::None), Point(Point)
{
}

FCellInfo::FCellInfo(ECellClosedSide ClosedSide, const FIntPoint& Point)
	: ClosedSide(ClosedSide), Point(Point)
{
}

FEquipment::FEquipment(uint64 ShapeValue)
: ShapeValue(ShapeValue),
  StatValue(FMath::RandRange(1, FEquipmentUtility::MaxStatValue)),
  Color(FColor::MakeRandomColor())
{
	for (int32 i = 0; i < FEquipmentUtility::MaxBoardValidCellCount; ++i)
	{
		uint64 ShiftedValue = ShapeValue << (i / FEquipmentUtility::MaxBoardColumn * 8 + i % FEquipmentUtility::MaxBoardColumn); 
		if (ShiftedValue & FEquipmentUtility::TopBitOne)
		{
			Cells.Emplace(FIntPoint { i % FEquipmentUtility::MaxBoardColumn, i / FEquipmentUtility::MaxBoardColumn });
		}

		if ((~ShiftedValue & FEquipmentUtility::MaxShapeValue) == FEquipmentUtility::MaxShapeValue)
		{
			break;
		}
	}

	auto FindPoint = [this](const FIntPoint& Point)
	{
		return Cells.FindByPredicate([Point](const FCellInfo& CellInfo)
		{
			return Point == CellInfo.Point;
		}) != nullptr;
	};

	for (auto & Cell : Cells)
	{
		ECellClosedSide ClosedSide = ECellClosedSide::None;
		FIntPoint Top = FIntPoint {Cell.Point.X, Cell.Point.Y - 1};
		FIntPoint Bottom = FIntPoint {Cell.Point.X, Cell.Point.Y + 1};
		FIntPoint Right = FIntPoint {Cell.Point.X + 1, Cell.Point.Y};
		FIntPoint Left = FIntPoint {Cell.Point.X - 1, Cell.Point.Y};

		if (FindPoint(Top))
		{
			ClosedSide |= ECellClosedSide::Top;
		}

		if (FindPoint(Bottom))
		{
			ClosedSide |= ECellClosedSide::Bottom;
		}

		if (FindPoint(Left))
		{
			ClosedSide |= ECellClosedSide::Left;
		}

		if (FindPoint(Right))
		{
			ClosedSide |= ECellClosedSide::Right;
		}

		Cell.ClosedSide = ClosedSide;
	}
}