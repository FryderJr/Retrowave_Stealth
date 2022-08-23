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

void ARSGameMode::SetGameState(ERSGameState State)
{
    if (RetrowaveGameState == State) return;
    
    RetrowaveGameState = State;
    
    OnGameStateChanged.Broadcast(RetrowaveGameState);
}
