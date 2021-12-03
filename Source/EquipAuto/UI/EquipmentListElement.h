// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentListElement.generated.h"

class UEquipmentBoard;
class UTextBlock;
/**
 * 
 */
UCLASS()
class EQUIPAUTO_API UEquipmentListElement : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual bool IsListItemSelectable() const override;

private:
	TWeakObjectPtr<UEquipmentBoard> EquipmentBoard;
	
	UPROPERTY(EditAnywhere)
	FColor SelectColor;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Count = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalStat = nullptr;
};
