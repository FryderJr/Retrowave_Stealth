// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameMode.h"
#include "Player/RSBaseCharacter.h"
#include "Player/RSPlayerController.h"
#include "UI/RSPlayerHUD.h"

ARSGameMode::ARSGameMode()
{
    DefaultPawnClass = ARSBaseCharacter::StaticClass();
    PlayerControllerClass = ARSPlayerController::StaticClass();
    HUDClass = ARSPlayerHUD::StaticClass();
}

void ARSGameMode::StartPlay()
{
    Super::StartPlay();
    SetGameState(ERSGameState::InProgress);
}

bool ARSGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto bIsPaused = Super::SetPause(PC, CanUnpauseDelegate);
    if (bIsPaused)
    {
        SetGameState(ERSGameState::Pause);
    }
    return bIsPaused;
}

bool ARSGameMode::ClearPause()
{
    const auto bIsPauseClear = Super::ClearPause();
    if (bIsPauseClear)
    {
        SetGameState(ERSGameState::InProgress);
    }
    return bIsPauseClear;
}

void ARSGameMode::SetGameState(ERSGameState State)
{
    if (RetrowaveGameState == State) return;
    
    RetrowaveGameState = State;
    
    OnGameStateChanged.Broadcast(RetrowaveGameState);
}
