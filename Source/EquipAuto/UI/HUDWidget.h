// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class UEquipmentBoard;
class UListView;
class UEquipmentboard_Widget;
/**
 * 
 */
UCLASS()
class EQUIPAUTO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
public:	
	void AddEquipmentBoard(const TArray<UEquipmentBoard*>& EquipmentBoards) const;
	void AddEquipmentBoard(UEquipmentBoard* EquipmentBoard) const;

private:
	void OnItemSelectionChanged(UObject* SelectedItem) const;
	void OnEntryWidgetGenerated(UUserWidget& UserWidget) const;
	
public:
	UPROPERTY(meta = (BindWidget))
	UEquipmentboard_Widget* Equipmentboard = nullptr;

	UPROPERTY(meta = (BindWidget))
	UListView* ListView = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalCount = nullptr;
};
