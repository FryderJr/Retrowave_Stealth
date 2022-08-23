// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/RSMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RSGameInstance.h"

void URSMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (StartPlayButton)
    {
        StartPlayButton->OnClicked.AddDynamic(this, &URSMenuWidget::OnStartPlay);
    }
    
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &URSMenuWidget::OnQuitGame);
    }
}
    
void URSMenuWidget::OnStartPlay()
{
    if (!GetWorld()) return;
    const auto RSGameInstance = GetWorld()->GetGameInstance<URSGameInstance>();
    
    if (!RSGameInstance) return;
    
    if (RSGameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogTemp, Warning, TEXT("No any StartLevel set yet"));
        return;
    }
    UGameplayStatics::OpenLevel(this, RSGameInstance->GetStartupLevelName());
}

void URSMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
