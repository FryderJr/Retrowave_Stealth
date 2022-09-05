// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/RSPlayerController.h"
#include "RSGameMode.h"
#include "RSBaseCharacter.h"

#include "EngineUtils.h"
#include "Interactable/RSTerminal.h"
#include "Camera/CameraActor.h"

void ARSPlayerController::BeginPlay()
{
    Super::BeginPlay();
    check(GetWorld());

    if (const auto GameMode = Cast<ARSGameMode>(GetWorld()->GetAuthGameMode()))
    {
        GameMode->OnGameStateChanged.AddUObject(this, &ARSPlayerController::OnGameStateChanged);
    }

    for (const auto& Terminal : TActorRange<ARSTerminal>(GetWorld()))
    {
        Terminal->OnInteractionStart.AddUObject(this, &ARSPlayerController::OnInteractionStart);
        Terminal->OnInteractionStop.AddUObject(this, &ARSPlayerController::OnInteractionStop);
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
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ARSPlayerController::OnInteractionStart(ACameraActor* Camera)
{
    if (!Camera) return;
    SetViewTargetWithBlend(Camera, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear, 0.f, true);

    const auto RSGameMode = Cast<ARSGameMode>(GetWorld()->GetAuthGameMode());
    if (!RSGameMode) return;
    RSGameMode->InteractWithObject();
}

void ARSPlayerController::OnInteractionStop()
{
    SetViewTargetWithBlend(GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear, 0.f, true);

    const auto RSGameMode = Cast<ARSGameMode>(GetWorld()->GetAuthGameMode());
    if (!RSGameMode) return;
    RSGameMode->StopInteraction();
}

