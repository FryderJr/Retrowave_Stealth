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

void ARSGameMode::SetGameState(ERSGameState State)
{
    RetrowaveGameState = State;
}
