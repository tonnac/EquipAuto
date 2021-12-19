#include "EquipmentUtility.h"
#include "EquipAutoInstance.h"

UWorld* FEquipmentUtility::GameWorld = nullptr;

bool FEquipmentUtility::IsValidPosition(const FIntPoint& Point)
{
	const FIntPoint BoardSize = GetBoardSize();
	return !(Point.X < 0 || Point.Y < 0 || Point.X >= BoardSize.X || Point.Y >= BoardSize.Y);
}

UEquipAutoInstance* FEquipmentUtility::GetGameInstance()
{
	return Cast<UEquipAutoInstance>( GameWorld->GetGameInstance());
}

FIntPoint FEquipmentUtility::GetBoardSize()
{
	return GetGameInstance()->GetBoardSize();
}

int32 FEquipmentUtility::GetBoardCount()
{
	auto BoardSize = GetBoardSize();
	return BoardSize.X * BoardSize.Y;
}

int32 FEquipmentUtility::GetCanEquipPosition(uint64 SourceValue, uint64 ShapeValue, const FIntPoint& BoardSize)
{
	for (int32 i = 0; i < BoardSize.X * BoardSize.Y; ++i)
	{
		const int32 Position = i / BoardSize.X * 8 + i % BoardSize.X;
		const uint64 MovedShapeValue = ShapeValue >> Position;

		if ((~SourceValue & MovedShapeValue) == MovedShapeValue)
		{
			return Position;
		}
	}
	return InvalidPosition;
}
