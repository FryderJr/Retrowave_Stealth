// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RSLibraryWidget.h"
#include "Components/Button.h"
#include "RSGameInstance.h"

void URSLibraryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    const auto GI = GetWorld()->GetGameInstance<URSGameInstance>();
    if (GI)
    {
        OpendKnowleges = GI->GetInfoPoints();
    }

    if (NextKnowlege)
    {
        NextKnowlege->OnClicked.AddDynamic(this, &URSLibraryWidget::OnNextKnowlege);
    }
}

void URSLibraryWidget::OnNextKnowlege()
{
    if (OpendKnowleges == 0) return;
    const auto NextIndex = ++CurrentKnowlegeIndex % OpendKnowleges;
    ShowCurrentKnowlege(NextIndex);
}

void URSLibraryWidget::ShowCurrentKnowlege(int32 Index)
{
    if (!FoundKnowledges.IsValidIndex(Index)) return;
    CurrentKnowlege = FoundKnowledges[Index];
}
