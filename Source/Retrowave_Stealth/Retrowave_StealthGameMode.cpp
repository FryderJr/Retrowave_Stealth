// Copyright Epic Games, Inc. All Rights Reserved.

#include "Retrowave_StealthGameMode.h"
#include "Retrowave_StealthCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARetrowave_StealthGameMode::ARetrowave_StealthGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
