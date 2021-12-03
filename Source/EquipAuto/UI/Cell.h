// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cell.generated.h"


enum class ECellClosedSide : uint8;
class UOverlaySlot;
class UImage;
/**
 * 
 */
UCLASS()
class EQUIPAUTO_API UCell : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	void SetColor(FColor Color, ECellClosedSide ClosedSide) const;
	void ResetCell() const;
private:
	UPROPERTY(EditAnywhere)
	float ImagePadding = 0;
	
	UPROPERTY()	
	UImage* Image = nullptr;

	TWeakObjectPtr<UOverlaySlot> ImageOverlaySlot = nullptr;
};
