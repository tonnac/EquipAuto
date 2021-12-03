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
