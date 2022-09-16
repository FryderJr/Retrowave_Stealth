// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSGamePauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RSGameInstance.h"

void URSGamePauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &URSGamePauseWidget::OnClearPause);
    }
    
    if (GoToMainMenuButton)
    {
        GoToMainMenuButton->OnClicked.AddDynamic(this, &URSGamePauseWidget::OnGoToMainMenu);
    }
}

void URSGamePauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}

void URSGamePauseWidget::OnGoToMainMenu()
{
    if (!GetWorld()) return;
    
    const auto RSGameInstance = GetWorld()->GetGameInstance<URSGameInstance>();
    if (!RSGameInstance) return;
    
    if (RSGameInstance->GetMenuLevelName().IsNone()) return;
    
    // save player's last checkpoint
    
    UGameplayStatics::OpenLevel(this, RSGameInstance->GetMenuLevelName());
}
