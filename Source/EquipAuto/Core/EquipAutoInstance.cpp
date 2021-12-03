// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipAutoInstance.h"
#include "Equipment.h"
#include "EquipmentShapePool.h"
#include "EquipmentUtility.h"

void UEquipAutoInstance::Init()
{
	Super::Init();
	InitEquipments();
}

void UEquipAutoInstance::InitEquipments()
{
	Equipments.Empty();
	for (const auto & ShapePool : FEquipmentShapePool::ShapePool)
	{
		const auto MaxCount = GetCanEquipMaxCount(ShapePool);

		for (int32 i = 0; i < MaxCount; ++i)
		{
			AddEquipment(ShapePool);
		}
	}
	SetDefaultBoardValue();
}

int32 UEquipAutoInstance::GetCanEquipMaxCount(uint64 Shape) const
{
	return X * Y / FMath::CountBits(Shape);	
}

TArray<TSharedPtr<FEquipment>>* UEquipAutoInstance::GetEquipments(uint64 ShapeValue)
{
	return Equipments.Find(ShapeValue);
}

TSharedPtr<FEquipment> UEquipAutoInstance::GetRandomEquipment() const
{
	const int32 Index = FMath::RandRange(0, Equipments.Num() - 1);

	auto Iter = Equipments.begin();

	int32 i = 0;
	for (; Iter != Equipments.end(); ++Iter, ++i)
	{
		if (i != Index)
		{
			continue;
		}

		const int32 ArrayIndex = FMath::RandRange(0, Iter->Value.Num() - 1);
		return Iter->Value[ArrayIndex];
	}
	return nullptr;
}

void UEquipAutoInstance::SetBoardSize(const FIntPoint& Point)
{
	X = Point.X;
	Y = Point.Y;
	OnSetBoardSizeEvent.Broadcast(GetBoardSize());
	InitEquipments();
}

int32 UEquipAutoInstance::GetColumnSize() const
{
	return X;
}

int32 UEquipAutoInstance::GetRowSize() const
{
	return Y;
}

FIntPoint UEquipAutoInstance::GetBoardSize() const
{
	return { X, Y };
}

uint64 UEquipAutoInstance::GetDefaultBoardValue() const
{
	return DefaultBoardValue;
}

const TMap<uint64, TArray<TSharedPtr<FEquipment>>>& UEquipAutoInstance::GetEquipments() const
{
	return Equipments;
}

void UEquipAutoInstance::SetDefaultBoardValue()
{
	TBitArray<TFixedAllocator<2>> BitArray {true, 64};

	const FIntPoint BoardSize = GetBoardSize();
	
	for (int32 i = 0; i < FEquipmentUtility::MaxBoardValidCellCount; ++i)
	{
		const int32 XPos = i % FEquipmentUtility::MaxBoardColumn;
		const int32 YPos = i / FEquipmentUtility::MaxBoardColumn;

		if (XPos < BoardSize.X && YPos < BoardSize.Y)
		{
			BitArray[FEquipmentUtility::MaxBoardValidCellCount - (1 + i)] = false;
		}
	}

	FMemory::Memcpy(&DefaultBoardValue, BitArray.GetData(), sizeof DefaultBoardValue);
}
