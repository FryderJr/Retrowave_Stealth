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
        //OpendKnowleges = GI->GetInfoPoints();
    }

    OpendKnowleges = 3;

    if (NextKnowlege)
    {
        NextKnowlege->OnClicked.AddDynamic(this, &URSLibraryWidget::OnNextKnowlege);
    }
}

void URSLibraryWidget::OnNextKnowlege()
{
    if (OpendKnowleges == 0) return;
    const auto NextIndex = ++CurrentKnowlegeIndex % OpendKnowleges;
    UE_LOG(LogTemp, Display, TEXT("Next"));
    ShowCurrentKnowlege(NextIndex);
}

void URSLibraryWidget::ShowCurrentKnowlege(int32 Index)
{
    if (!FoundKnowledges.IsValidIndex(Index)) return;
    UE_LOG(LogTemp, Display, TEXT("slide∆ %i"), Index);
    CurrentKnowlege = FoundKnowledges[Index];
}
