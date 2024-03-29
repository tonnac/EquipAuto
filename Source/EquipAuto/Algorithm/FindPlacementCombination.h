﻿#pragma once

struct FEquipmentInfo;
class UEquipmentBoard;

struct FFindPlacementCombination
{
	static TArray<UEquipmentBoard*> FindCombination(int32 PoolNumber);
	static TArray<UEquipmentBoard*> FindCombinationByRandomPool(int32 PoolNumber);

private:
	static TArray<uint64> ShapePools;
	static TArray<UEquipmentBoard*> Find(UEquipmentBoard*& Board, TMap<uint64, TSet<int32>>& Pos);
	static TArray<UEquipmentBoard*> Find(UEquipmentBoard*& Board);
	static TArray<UEquipmentBoard*> FindNumberOfCases(UEquipmentBoard*& Board);
	static TArray<UEquipmentBoard*> Search(UEquipmentBoard*& SourceBoard, const TMap<void*, TSharedPtr<FEquipmentInfo>>& Equipments, TSet<uint64> ShapeValues);
};
