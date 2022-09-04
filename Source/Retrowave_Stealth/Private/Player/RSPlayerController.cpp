// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RSPlayerController.h"
#include "RSGameMode.h"
#include "RSBaseCharacter.h"

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

void ARSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;
    
    InputComponent->BindAction("SetPause", IE_Pressed, this, &ARSPlayerController::OnGamePaused);
}

void ARSPlayerController::OnGamePaused()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ARSPlayerController::OnGameStateChanged(ERSGameState State)
{
    UE_LOG(LogTemp, Display, TEXT("GemeState: %s"), *UEnum::GetValueAsString(State));
    if (State == ERSGameState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
        
        const auto BaseCharacter = Cast<ARSBaseCharacter>(GetPawn());
        if (BaseCharacter)
        {
            BaseCharacter->StopInteraction();
        }
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

