// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TowerDefenseGameMode.h"
#include "TowerDefenseHUD.h"
#include "TowerDefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATowerDefenseGameMode::ATowerDefenseGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATowerDefenseHUD::StaticClass();
}
