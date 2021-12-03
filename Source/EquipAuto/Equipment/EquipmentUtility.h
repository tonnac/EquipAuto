#pragma once

class UEquipAutoInstance;

class FEquipmentUtility
{
public:
	static bool IsValidPosition(const FIntPoint& Point);

	static UEquipAutoInstance* GetGameInstance();
	static UWorld* GameWorld;
	static FIntPoint GetBoardSize();
	static int32 GetBoardCount();
	
	static constexpr int32 MaxBoardRow = 8;
	static constexpr int32 MaxBoardColumn = 8;
	static constexpr int32 MaxBoardValidCellCount = MaxBoardColumn * MaxBoardRow;
	static constexpr uint64 MaxEquipmentBoardValue = 217020518514294783ull;
	static constexpr uint64 TopBitOne = 9223372036854775808ull;
	static constexpr uint64 MaxShapeValue = TNumericLimits<uint64>::Max();
	static constexpr int32 MaxStatValue = 2000;
	static constexpr int32 InvalidPosition = -1;
	static constexpr uint64 DefaultBoardValue = 217020518514294783ull;
};
