#pragma once

#include "CoreMinimal.h"
#include "EquipmentUtility.h"
#include "UObject/Object.h"
#include "EquipmentBoard.generated.h"

struct FEquipmentInfo;
struct FEquipment;


UCLASS()
class EQUIPAUTO_API UEquipmentBoard : public UObject 
{
	GENERATED_BODY()
public:
	void Init();
	
public:
	TSharedPtr<FEquipmentInfo> AddEquipment(const TSharedPtr<FEquipment>& Equipment);
	TSharedPtr<FEquipmentInfo> AddEquipment(const TSharedPtr<FEquipment>& Equipment, int32 Position);
	void RemoveEquipment(const TSharedPtr<FEquipment>& Equipment);

	int32 GetTotalStat() const;
	int32 GetCountEquipments() const;
	const TMap<void*, TSharedPtr<FEquipmentInfo>>& GetEquipments() const;

	uint64 GetBoardValue() const;
	int32 CanEquip(const TSharedPtr<FEquipment>& Equipment) const;
	int32 CanEquip(uint64 ShapeValue) const;
	bool IsMaxBoard() const;
	bool IsEquip(const TSharedPtr<FEquipment>& Equipment) const;

	void CopyBoard(const UEquipmentBoard* SourceBoard);
	
private:
	int32 TotalStat = 0;
	uint64 BoardValue = FEquipmentUtility::DefaultBoardValue;
	TMap<void*, TSharedPtr<FEquipmentInfo>> Equipments;
};
