// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RSPlayerController.h"
#include "RSGameMode.h"

void ARSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (GetWorld())
    {
        if (const auto GameMode = Cast<ARSGameMode>(GetWorld()->GetAuthGameMode()))
        {
            GameMode->OnGameStateChanged.AddUObject(this, &ARSPlayerController::OnGameStateChanged);
        }
    }
}

void ARSPlayerController::OnGameStateChanged(ERSGameState State)
{
    UE_LOG(LogTemp, Display, TEXT("GemeState: %s"), *UEnum::GetValueAsString(State));
    if (State == ERSGameState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}
