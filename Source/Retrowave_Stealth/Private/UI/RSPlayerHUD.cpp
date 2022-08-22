// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSPlayerHUD.h"
#include "RSGameMode.h"

void ARSPlayerHUD::BeginPlay()
{
    Super::BeginPlay();
    
    if (GetWorld())
    {
        const auto RSGameMode = Cast<ARSGameMode>(GetWorld()->GetAuthGameMode());
        if (RSGameMode)
        {
            RSGameMode->OnGameStateChanged.AddUObject(this, &ARSPlayerHUD::OnGameStateChanged);
        }
    }
}

void ARSPlayerHUD::OnGameStateChanged(ERSGameState)
{
    
}
