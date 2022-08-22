// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/UI/RSMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void URSMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (StartPlayButton)
    {
        StartPlayButton->OnClicked.AddDynamic(this, &URSMenuWidget::OnStartPlay);
    }
}
    
void URSMenuWidget::OnStartPlay()
{
    const FName StartupLevelName = NAME_None;
    UGameplayStatics::OpenLevel(this, StartupLevelName);
}
