#pragma once
#include "Equipment.h"

struct FEquipmentInfo
{
	FEquipmentInfo(const TSharedPtr<FEquipment>& Equipment, int32 Position);

	TArray<FCellInfo> GetMovedCells() const;

	friend bool operator==(const FEquipmentInfo& Lhs, const FEquipmentInfo& RHS)
	{
		return Lhs.Equipment == RHS.Equipment;
	}

	friend bool operator!=(const FEquipmentInfo& Lhs, const FEquipmentInfo& RHS)
	{
		return !(Lhs == RHS);
	}

	TSharedPtr<FEquipment> Equipment;
	int32 Position = 0;
};
