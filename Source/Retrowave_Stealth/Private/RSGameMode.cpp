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
    UpdateTerminalData();
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

    const auto MyGameInstance = Cast<URSGameInstance>(GetGameInstance());
    if (MyGameInstance)
    {
        MyGameInstance->SetInfoPoints(CurrentTerminalData.TerminalsNum - CurrentTerminalData.ActiveTerminalsNum);
    }
}

void ARSGameMode::AddSpottedBy(AActor* Enemy)
{
    PlayerSpottedBy.AddUnique(Enemy);
    PlayerStatusChanged(GetSpottedByNum(), GetAlertedByNum());
}

void ARSGameMode::AddAlertedBy(AActor* Enemy)
{
    PlayerAlertedBy.AddUnique(Enemy);
    PlayerStatusChanged(GetSpottedByNum(), GetAlertedByNum());
}

void ARSGameMode::DeleteSpottedBy(AActor* Enemy)
{
    PlayerSpottedBy.Remove(Enemy);
    PlayerStatusChanged(GetSpottedByNum(), GetAlertedByNum());
}

void ARSGameMode::DeleteAlertedBy(AActor* Enemy)
{
    PlayerAlertedBy.Remove(Enemy);
    PlayerStatusChanged(GetSpottedByNum(), GetAlertedByNum());
}

int32 ARSGameMode::GetSpottedByNum()
{
    return PlayerSpottedBy.Num();
}

int32 ARSGameMode::GetAlertedByNum()
{
    return PlayerAlertedBy.Num();
}

void ARSGameMode::StartPlay()
{
    Super::StartPlay();
    SetGameState(ERSGameState::InProgress);

    InitTerminals();

    UpdateTerminalData();
}

void ARSGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    
    FString SelectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame");
    if (SelectedSaveSlot.Len() <= 0) return;
    
    URSGameInstance* MyGameInstance = Cast<URSGameInstance>(GetGameInstance());
    if (!MyGameInstance) return;
        
    MyGameInstance->LoadGame();
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

void ARSGameMode::InitTerminals()
{
    if (!GetWorld()) return;

    for (const auto& Terminal : TActorRange<ARSTerminal>(GetWorld()))
    {
        ++CurrentTerminalData.TerminalsNum;
        Terminal->OnInteractionStart.AddUObject(this, &ARSGameMode::OnInteractionStart);
        Terminal->OnInteractionStop.AddUObject(this, &ARSGameMode::OnInteractionStop);
    }
}

void ARSGameMode::SetGameState(ERSGameState State)
{
    if (RetrowaveGameState == State) return;
    
    RetrowaveGameState = State;
    
    OnGameStateChanged.Broadcast(RetrowaveGameState);
}

void ARSGameMode::OnInteractionStart(ACameraActor* Camera)
{
    SetGameState(ERSGameState::Interact);
}

void ARSGameMode::OnInteractionStop()
{
    SetGameState(ERSGameState::InProgress);
    UpdateTerminalData();
}
