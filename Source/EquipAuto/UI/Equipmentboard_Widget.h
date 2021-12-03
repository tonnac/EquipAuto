// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Equipmentboard_Widget.generated.h"

class UEquipmentBoard;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class EQUIPAUTO_API UEquipmentboard_Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void SetEquipmentboard(const UEquipmentBoard* Equipmentboard);

public:
	void ResetBoard() const;
	
private:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UGridPanel = nullptr;

	TWeakObjectPtr<const UEquipmentBoard> EquipmentBoard = nullptr;
};
