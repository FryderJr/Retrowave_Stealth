// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameMode.h"
#include "RSGameInstance.h"
#include "Player/RSBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RSPlayerController.h"
#include "UI/RSPlayerHUD.h"
#include "Interactable/RSTerminal.h"
#include "EngineUtils.h"

ARSGameMode::ARSGameMode()
{
    DefaultPawnClass = ARSBaseCharacter::StaticClass();
    PlayerControllerClass = ARSPlayerController::StaticClass();
    HUDClass = ARSPlayerHUD::StaticClass();
}

void ARSGameMode::InteractWithObject()
{
    SetGameState(ERSGameState::Interact);
}

void ARSGameMode::StopInteraction()
{
    SetGameState(ERSGameState::InProgress);
}

void ARSGameMode::UpdateTerminalData()
{
    CurrentTerminalData.ActiveTerminalsNum = 0;
    CurrentTerminalData.HackedSuccesTerminalsNum = 0;
    for (const auto& Terminal : TActorRange<ARSTerminal>(GetWorld()))
    {
        CurrentTerminalData.ActiveTerminalsNum += Terminal->GetWorkingStatus();
        CurrentTerminalData.HackedSuccesTerminalsNum += Terminal->GetHackedStatus();
    }
}

void ARSGameMode::StartPlay()
{
    Super::StartPlay();
    SetGameState(ERSGameState::InProgress);

    for (const auto& Terminal : TActorRange<ARSTerminal>(GetWorld()))
    {
        ++CurrentTerminalData.TerminalsNum;
    }
    UpdateTerminalData();
}

void ARSGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    
    FString SelectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame");
    if (SelectedSaveSlot.Len() > 0)
    {
        URSGameInstance* MyGameInstance = Cast<URSGameInstance>(GetGameInstance());
        if (!MyGameInstance) return;
        
        MyGameInstance->LoadGame();
    }
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
