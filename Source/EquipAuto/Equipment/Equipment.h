#pragma once

enum class ECellClosedSide : uint8;

struct FCellInfo
{
	FCellInfo();
	FCellInfo(const FIntPoint& Point);
	FCellInfo(ECellClosedSide ClosedSide, const FIntPoint& Point);
	
	ECellClosedSide ClosedSide;
	FIntPoint Point;
};

struct FEquipment
{
	FEquipment(uint64 ShapeValue);
	
	uint64 ShapeValue = 0;
	int32 StatValue = 0;
	FColor Color;
	TArray<FCellInfo> Cells;
};
