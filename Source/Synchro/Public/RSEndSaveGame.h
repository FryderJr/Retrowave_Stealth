// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RSEndSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SYNCHRO_API URSEndSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	int32 TerminalPoints;
};
