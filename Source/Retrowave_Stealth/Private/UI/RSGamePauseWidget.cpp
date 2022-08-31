// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSGamePauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

void URSGamePauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &URSGamePauseWidget::OnClearPause);
    }
}

void URSGamePauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}
