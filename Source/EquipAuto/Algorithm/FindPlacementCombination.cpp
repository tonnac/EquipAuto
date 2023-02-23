#include "FindPlacementCombination.h"

#include "EquipAutoInstance.h"
#include "EquipmentBoard.h"
#include "EquipmentInfo.h"
#include "EquipmentShapePool.h"
#include "EquipmentUtility.h"

TArray<uint64> FFindPlacementCombination::ShapePools;

TArray<UEquipmentBoard*> FFindPlacementCombination::FindCombination(int32 PoolNumber)
{
	ShapePools.Reset();
	
	PoolNumber = FMath::Clamp(PoolNumber, 1, FEquipmentShapePool::ShapePool.Num());
	ShapePools.Append(FEquipmentShapePool::ShapePool.GetData(), PoolNumber);
	UEquipmentBoard* EquipmentBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld,
	                                                             UEquipmentBoard::StaticClass());
	EquipmentBoard->Init();

	while (!EquipmentBoard->IsMaxBoard())
	{
		for (int32 i = 0; i < ShapePools.Num(); ++i)
		{
			const uint64 ShapeValue = ShapePools[i];
			if (TArray<TSharedPtr<FEquipment, ESPMode::Fast>>* Equipments = FEquipmentUtility::GetGameInstance()->
			GetEquipments(ShapeValue))
			{
				if (const int32 Position = EquipmentBoard->CanEquip(ShapeValue); Position != FEquipmentUtility::InvalidPosition)
				{
					int32 Index = 0;
					while (EquipmentBoard->IsEquip((*Equipments)[Index]))
					{
						Index++;
					}
					EquipmentBoard->AddEquipment((*Equipments)[Index], Position);
				}
			}
		}
	}

	return FindNumberOfCases(EquipmentBoard);
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

TArray<UEquipmentBoard*> FFindPlacementCombination::FindNumberOfCases(UEquipmentBoard*& Board)
{
	const TMap<void*, TSharedPtr<FEquipmentInfo>>& Equipments = Board->GetEquipments();
	TSet<uint64> ShapeValues;

	TArray<UEquipmentBoard*> Boards;
	
	for (const auto& Equipment : Equipments)
	{
		uint64 ShapeValue = Equipment.Value->Equipment->ShapeValue;
		if (ShapeValues.Contains(ShapeValue))
		{
			continue;
		}
		TArray<int32> CanEquipPositions = FEquipmentUtility::GetCanEquipPositions(ShapeValue, FEquipmentUtility::GetGameInstance()->GetDefaultBoardValue());
		for (const int32 CanEquipPosition : CanEquipPositions)
		{
			UEquipmentBoard* NewBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld, UEquipmentBoard::StaticClass());
			NewBoard->Init();
			NewBoard->AddEquipment(Equipment.Value->Equipment, CanEquipPosition);

			Boards.Append(Search(NewBoard, Equipments, ShapeValues));
		}
		ShapeValues.Emplace(ShapeValue);
	}
	return Boards;
}

TArray<UEquipmentBoard*> FFindPlacementCombination::Search(UEquipmentBoard*& SourceBoard,
	const TMap<void*, TSharedPtr<FEquipmentInfo>>& Equipments, TSet<uint64> ShapeValues)
{
	if (SourceBoard->IsMaxBoard())
	{
		return { SourceBoard };
	}
	
	TArray<UEquipmentBoard*> EquipmentBoards;
	const uint64 SourceValue = SourceBoard->GetBoardValue();
	for (const auto& Equipment : Equipments)
	{
		const uint64 ShapeValue = Equipment.Value->Equipment->ShapeValue;
		if (!SourceBoard->IsEquip(Equipment.Value->Equipment) && !ShapeValues.Contains(ShapeValue))
		{
			TArray<int32> CanEquipPositions = FEquipmentUtility::GetCanEquipPositions(ShapeValue, SourceValue);
			for (const int32 CanEquipPosition : CanEquipPositions)
			{
				UEquipmentBoard* NewBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld, UEquipmentBoard::StaticClass());
				NewBoard->Init();
				NewBoard->CopyBoard(SourceBoard);
				NewBoard->AddEquipment(Equipment.Value->Equipment, CanEquipPosition);

				EquipmentBoards.Append(Search(NewBoard, Equipments, ShapeValues));
			}
		}
	}
	return EquipmentBoards;
}
