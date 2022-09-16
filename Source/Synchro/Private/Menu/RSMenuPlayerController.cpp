// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/RSMenuPlayerController.h"

void ARSMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
