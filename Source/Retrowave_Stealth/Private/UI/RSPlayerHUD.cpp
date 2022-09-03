// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSPlayerHUD.h"
#include "RSGameMode.h"
#include "Blueprint/UserWidget.h"

void ARSPlayerHUD::BeginPlay()
{
    Super::BeginPlay();
    
    GameWidgets.Add(ERSGameState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass));
    GameWidgets.Add(ERSGameState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ERSGameState::PlayMiniGame, CreateWidget<UUserWidget>(GetWorld(), MiniGameWidgetClass));
    
    for (auto& GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;
        
        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if (GetWorld())
    {
        const auto RSGameMode = Cast<ARSGameMode>(GetWorld()->GetAuthGameMode());
        if (RSGameMode)
        {
            RSGameMode->OnGameStateChanged.AddUObject(this, &ARSPlayerHUD::OnGameStateChanged);
        }
    }
}

void ARSPlayerHUD::OnGameStateChanged(ERSGameState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}
