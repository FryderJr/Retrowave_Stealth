// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSInteractionWidget.h"
#include "Components/HorizontalBox.h"
#include "MiniGame/MiniGame.h"

void URSInteractionWidget::InitMiniGame()
{
    if (!MiniGameBox) return;
    MiniGameBox->ClearChildren();

    const auto MiniGame = CreateWidget<UUserWidget>(GetWorld(), TutorialWidgetClass);
    if (MiniGame)
    {
        MiniGameBox->AddChild(MiniGame);
    }
}

void URSInteractionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (TutorialBox)
    {
        TutorialBox->ClearChildren();
        
        const auto Tutorial = CreateWidget<UUserWidget>(GetWorld(), TutorialWidgetClass);
        if (Tutorial)
        {
            TutorialBox->AddChild(Tutorial);
        }
    }
}
