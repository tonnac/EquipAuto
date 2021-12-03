// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EquipAutoGameModeBase.generated.h"

class UHUDWidget;
class UEquipmentBoard;
/**
 * 
 */
UCLASS()
class EQUIPAUTO_API AEquipAutoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	void FindCombination(int32 PoolIndex);

	UFUNCTION(BlueprintCallable)
	void FindCombinationByRandomPool(int32 PoolNumber);
	
protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(Transient)
	TArray<UEquipmentBoard*> Boards;
	
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UHUDWidget> HudPath;

	UPROPERTY()
	UHUDWidget* HUD = nullptr;
};
