// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RSTypes.h"
#include "RSGameMode.generated.h"


UCLASS()
class RETROWAVE_STEALTH_API ARSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ARSGameMode();
    
    FOnGameStateChagedSignature OnGameStateChanged;
    
protected:
    virtual void StartPlay() override;
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    
private:
    ERSGameState RetrowaveGameState = ERSGameState::WaitingToStart;
    
    void SetGameState(ERSGameState State);
};
