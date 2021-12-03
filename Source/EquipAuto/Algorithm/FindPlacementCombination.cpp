#include "FindPlacementCombination.h"

#include "EquipAutoInstance.h"
#include "EquipmentBoard.h"
#include "EquipmentShapePool.h"
#include "EquipmentUtility.h"

TArray<uint64> FFindPlacementCombination::ShapePools;

TArray<UEquipmentBoard*> FFindPlacementCombination::FindCombination(int32 PoolNumber)
{
	ShapePools.Reset();
	
	PoolNumber = FMath::Clamp(PoolNumber, 1, FEquipmentShapePool::ShapePool.Num());
	ShapePools.Append(FEquipmentShapePool::ShapePool.GetData(), PoolNumber);
	const UEquipAutoInstance* GameInstance = FEquipmentUtility::GetGameInstance();

	uint64 Default = 0;

	TArray<UEquipmentBoard*> Boards;

	for (int32 i = 0; i < ShapePools.Num(); ++i)
	{
		const uint64 Value = ShapePools[i];
		const uint64 DefaultValue = GameInstance->GetDefaultBoardValue();

		const FIntPoint BoardSize = FEquipmentUtility::GetBoardSize();
		for (int32 j = 0; j < BoardSize.X * BoardSize.Y; ++j)
		{
			const int32 Position = j / BoardSize.X * 8 + j % BoardSize.X;
			const uint64 MovedShapeValue = Value >> Position;

			if ((Default & MovedShapeValue) == 0 && (~DefaultValue & MovedShapeValue) == MovedShapeValue)
			{
				TMap<uint64, TSet<int32>> Pos;
				auto EquipmentBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld, UEquipmentBoard::StaticClass());
				Pos.Emplace(MovedShapeValue);
				EquipmentBoard->Init();
				Boards.Append(Find(EquipmentBoard, Pos));
				Default |= MovedShapeValue;
				break;
			}
		}
	}
	
	return Boards;
}

TArray<UEquipmentBoard*> FFindPlacementCombination::FindCombinationByRandomPool(int32 PoolNumber)
{
	TArray<UEquipmentBoard*> EquipmentBoards;

	return EquipmentBoards;
}

TArray<UEquipmentBoard*> FFindPlacementCombination::Find(UEquipmentBoard*& Board, TMap<uint64, TSet<int32>>& Pos)
{
	TArray<UEquipmentBoard*> Boards;
	if (Board->IsMaxBoard())
	{
		return std::initializer_list<UEquipmentBoard*> { Board };
	}

	bool bCanEquip = false;
	for (int32 i = 0; i < ShapePools.Num(); ++i)
	{
		int32 Position = Board->CanEquip(ShapePools[i]);
		auto PosSet = Pos.Find(ShapePools[i]);
		if (Position != FEquipmentUtility::InvalidPosition)
		{
			if (nullptr == PosSet)
			{
				PosSet = &Pos.Emplace(ShapePools[i], TSet<int32> {});
			}
			
			bCanEquip = true;
			auto Equipments = FEquipmentUtility::GetGameInstance()->GetEquipments(ShapePools[i]);
			
			if (Equipments)
			{
				for (const auto & Equipment : *Equipments)
				{
					if (!Board->IsEquip(Equipment) && !PosSet->Contains(Position))
					{
						UEquipmentBoard* NewBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld, UEquipmentBoard::StaticClass());
						NewBoard->Init();
						NewBoard->CopyBoard(Board);
						NewBoard->AddEquipment(Equipment, Position);
						PosSet->Emplace(Position);
						auto EquipmentBoards = Find(NewBoard, Pos);
						if (EquipmentBoards.Num() > 0)
						{
							Boards.Append(MoveTemp(EquipmentBoards));
						}
					}
				}
			}
		}
	}

	return Boards;
}

TArray<UEquipmentBoard*> FFindPlacementCombination::Find(UEquipmentBoard*& Board)
{
	TArray<UEquipmentBoard*> Boards;
	if (Board->IsMaxBoard())
	{
		return std::initializer_list<UEquipmentBoard*> { Board };
	}

	bool bCanEquip = false;
	for (int32 i = 0; i < ShapePools.Num(); ++i)
	{
		int32 Position = Board->CanEquip(ShapePools[i]);
		if (Position != FEquipmentUtility::InvalidPosition)
		{
			bCanEquip = true;
			auto Equipments = FEquipmentUtility::GetGameInstance()->GetEquipments(ShapePools[i]);

			if (Equipments)
			{
				for (const auto & Equipment : *Equipments)
				{
					if (!Board->IsEquip(Equipment))
					{
						UEquipmentBoard* NewBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld, UEquipmentBoard::StaticClass());
						NewBoard->Init();
						NewBoard->CopyBoard(Board);
						NewBoard->AddEquipment(Equipment, Position);
						auto EquipmentBoards = Find(NewBoard);
						if (EquipmentBoards.Num() > 0)
						{
							Boards.Append(MoveTemp(EquipmentBoards));
						}
					}
				}
			}
		}
	}

	return Boards;
}