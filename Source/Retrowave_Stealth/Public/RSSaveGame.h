// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "RSSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class RETROWAVE_STEALTH_API URSSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Save)
	FTransform PlayerTransform;

};
