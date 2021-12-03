// Copyright Epic Games, Inc. All Rights Reserved.


#include "EquipAutoGameModeBase.h"

#include "EquipAutoInstance.h"
#include "EquipmentBoard.h"
#include "EquipmentUtility.h"
#include "HUDWidget.h"
#include "FindPlacementCombination.h"
#include "Blueprint/UserWidget.h"
#include "Engine/AssetManager.h"

void AEquipAutoGameModeBase::FindCombination(int32 PoolIndex)
{
	auto EquipmentBoards = FFindPlacementCombination::FindCombination(PoolIndex);

	
	
	HUD->AddEquipmentBoard(EquipmentBoards);
}

void AEquipAutoGameModeBase::FindCombinationByRandomPool(int32 PoolNumber)
{
	auto EquipmentBoards = FFindPlacementCombination::FindCombinationByRandomPool(PoolNumber);

	
	
	HUD->AddEquipmentBoard(EquipmentBoards);
}

void AEquipAutoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	FEquipmentUtility::GameWorld = GetWorld();

	for (int32 i = 0; i < 20; ++i)
	{
		UEquipmentBoard* NewBoard = NewObject<UEquipmentBoard>(FEquipmentUtility::GameWorld, UEquipmentBoard::StaticClass());
		if (NewBoard)
		{
			NewBoard->Init();
			Boards.Emplace(NewBoard);
		}
	}

	for (const auto & Board : Boards)
	{
		for (int32 i = 0; i < 36; ++i)
		{
			TSharedPtr<FEquipmentInfo> EquipmentInfo = Board->AddEquipment(FEquipmentUtility::GetGameInstance()->GetRandomEquipment());
			while (!EquipmentInfo && !Board->IsMaxBoard())
			{
				EquipmentInfo = Board->AddEquipment(FEquipmentUtility::GetGameInstance()->GetRandomEquipment());
			}
		}
	}
	
	UClass* WidgetClass = HudPath.LoadSynchronous();
	
	if (WidgetClass)
	{
		UHUDWidget* HUDWidget = Cast<UHUDWidget>(CreateWidget(GetGameInstance(), WidgetClass, TEXT("HUD")));
		if (HUDWidget)
		{
			HUD = HUDWidget;
			HUD->AddToViewport();
			HUD->AddEquipmentBoard(Boards);
		}
	}
	
}
