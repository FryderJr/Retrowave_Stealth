// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RSTypes.h"
#include "RSPlayerHUD.generated.h"


UCLASS()
class RETROWAVE_STEALTH_API ARSPlayerHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
    virtual void BeginPlay() override;
    
private:
    void OnGameStateChanged(ERSGameState);
};
