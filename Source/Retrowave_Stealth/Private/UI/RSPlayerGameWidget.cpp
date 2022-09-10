// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/RSPlayerGameWidget.h"

bool URSPlayerGameWidget::NextPharese()
{
    if (Dialog.Num() == 0) return false;

    const bool bIsFinished = CurrentPhraseIndex == Dialog.Num() - 1;

    if (!bIsFinished)
    {
        CurrentPhraseIndex = ++CurrentPhraseIndex % Dialog.Num();
        CurrentPhrase = Dialog[CurrentPhraseIndex];
    }
    
    return bIsFinished;
}

void URSPlayerGameWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void URSPlayerGameWidget::StartDialog(int32 PhreseNumber)
{
    if (!Dialog.IsValidIndex(PhreseNumber)) return;
    CurrentPhraseIndex = PhreseNumber;
    CurrentPhrase = Dialog[CurrentPhraseIndex];
}

