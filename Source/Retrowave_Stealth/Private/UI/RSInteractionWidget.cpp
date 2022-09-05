// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSInteractionWidget.h"
#include "Components/HorizontalBox.h"
#include "MiniGame/MiniGame.h"

void URSInteractionWidget::InitMiniGame()
{
    //if (!MiniGameBox) return;
    //MiniGameBox->ClearChildren();

    //const auto MiniGame = CreateWidget<UMiniGame>(GetWorld(), MiniGameWidgetClass);
    //if (MiniGame)
    //{
    //    MiniGameBox->AddChild(MiniGame);
    //}
}

void URSInteractionWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}
