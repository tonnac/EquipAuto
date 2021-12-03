// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "EquipmentUtility.h"
#include "EquipAutoInstance.generated.h"

struct FEquipment;
/**
 * 
 */
UCLASS()
class EQUIPAUTO_API UEquipAutoInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

public:
	void InitEquipments();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetBoardSize, const FIntPoint&)
	FOnSetBoardSize OnSetBoardSizeEvent;

	int32 GetCanEquipMaxCount(uint64 Shape) const;

	TArray<TSharedPtr<FEquipment>>* GetEquipments(uint64 ShapeValue);

public:
	TSharedPtr<FEquipment> GetRandomEquipment() const;
	
	UFUNCTION(BlueprintCallable)
	void SetBoardSize(const FIntPoint& Point);

	UFUNCTION(BlueprintCallable)
	int32 GetColumnSize() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRowSize() const;

	FIntPoint GetBoardSize() const;

	uint64 GetDefaultBoardValue() const;

public:
	template <typename... ArgsType>
	TSharedPtr<FEquipment> AddEquipment(ArgsType&&... Args)
	{
		TSharedPtr<FEquipment> NewEquipment = MakeShared<FEquipment>(Forward<ArgsType>(Args)...);

		if (NewEquipment)
		{
			auto FindEquipments = Equipments.Find(NewEquipment->ShapeValue);

			if (FindEquipments)
			{
				FindEquipments->Emplace(NewEquipment);
			}
			else
			{
				Equipments.Emplace(NewEquipment->ShapeValue, std::initializer_list<TSharedPtr<FEquipment>> {NewEquipment});
			}
			return NewEquipment;
		}
		return nullptr;
	}
	const TMap<uint64, TArray<TSharedPtr<FEquipment>>>& GetEquipments() const;

private:
	void SetDefaultBoardValue();
	
private:
	uint64 DefaultBoardValue = FEquipmentUtility::DefaultBoardValue;
	
	TMap<uint64, TArray<TSharedPtr<FEquipment>>> Equipments;
	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax ="8"))
	int X = 6;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax ="8"))
	int Y = 6;
};