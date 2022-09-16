// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/RSMenuGameMode.h"
#include "Menu/RSMenuPlayerController.h"
#include "Menu/UI/RSMenuHUD.h"

ARSMenuGameMode::ARSMenuGameMode()
{
    PlayerControllerClass = ARSMenuPlayerController::StaticClass();
    HUDClass = ARSMenuHUD::StaticClass();
}
