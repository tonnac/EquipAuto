#include "EquipmentBoard.h"

#include "EquipAutoInstance.h"
#include "Equipment.h"
#include "EquipmentInfo.h"

void UEquipmentBoard::Init()
{
	BoardValue = FEquipmentUtility::GetGameInstance()->GetDefaultBoardValue();
}

TSharedPtr<FEquipmentInfo> UEquipmentBoard::AddEquipment(const TSharedPtr<FEquipment>& Equipment)
{
	const int32 Position = CanEquip(Equipment);

	if (Position != FEquipmentUtility::InvalidPosition)
	{
		return AddEquipment(Equipment, Position);
	}
	return nullptr;
}

TSharedPtr<FEquipmentInfo> UEquipmentBoard::AddEquipment(const TSharedPtr<FEquipment>& Equipment, int32 Position)
{
	TSharedPtr<FEquipmentInfo> EquipmentInfo = MakeShared<FEquipmentInfo>(Equipment, Position);
	BoardValue |= (Equipment->ShapeValue >> Position);
	TotalStat += Equipment->StatValue;
	Equipments.Emplace(Equipment.Get(), EquipmentInfo);
	return MoveTemp(EquipmentInfo);
}

void UEquipmentBoard::RemoveEquipment(const TSharedPtr<FEquipment>& Equipment)
{
	Equipments.Remove(Equipment.Get());
}

int32 UEquipmentBoard::GetTotalStat() const
{
	return TotalStat;
}

int32 UEquipmentBoard::GetCountEquipments() const
{
	return Equipments.Num();
}

const TMap<void*, TSharedPtr<FEquipmentInfo>>& UEquipmentBoard::GetEquipments() const
{
	return Equipments;
}

int32 UEquipmentBoard::CanEquip(const TSharedPtr<FEquipment>& Equipment) const
{
	return CanEquip(Equipment->ShapeValue);
}

int32 UEquipmentBoard::CanEquip(uint64 ShapeValue) const
{
	if (IsMaxBoard())
	{
		return FEquipmentUtility::InvalidPosition;	
	}

	const FIntPoint BoardSize = FEquipmentUtility::GetBoardSize();
	for (int32 i = 0; i < BoardSize.X * BoardSize.Y; ++i)
	{
		const int32 Position = i / BoardSize.X * 8 + i % BoardSize.X;
		const uint64 MovedShapeValue = ShapeValue >> Position;

		if ((~BoardValue & MovedShapeValue) == MovedShapeValue)
		{
			return Position;
		}
	}

	return FEquipmentUtility::InvalidPosition;
}

bool UEquipmentBoard::IsMaxBoard() const
{
	return BoardValue == FEquipmentUtility::MaxShapeValue;
}

bool UEquipmentBoard::IsEquip(const TSharedPtr<FEquipment>& Equipment) const
{
	return Equipments.Find(Equipment.Get()) != nullptr;
}

void UEquipmentBoard::CopyBoard(const UEquipmentBoard* SourceBoard)
{
	TotalStat = SourceBoard->TotalStat;
	BoardValue = SourceBoard->BoardValue;
	Equipments = SourceBoard->Equipments;
}
