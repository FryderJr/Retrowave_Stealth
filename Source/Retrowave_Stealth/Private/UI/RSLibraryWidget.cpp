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
        OpenedKnowleges = GI->GetInfoPoints();
    }

    OpenedKnowleges = 3;

    for (uint8 i = 0; i < OpenedKnowleges; ++i)
    {
        FoundKnowledges[i].bEnabled = true;
    }
    
    CurrentKnowlege = FoundKnowledges[CurrentKnowlegeIndex];

    if (NextKnowlegeButton)
    {
        NextKnowlegeButton->OnClicked.AddDynamic(this, &URSLibraryWidget::OnNextKnowlege);
    }

    if (PrevKnowlegeButton)
    {
        PrevKnowlegeButton->OnClicked.AddDynamic(this, &URSLibraryWidget::OnPrevKnowlege);
    }
}

void URSLibraryWidget::OnShowCurrentKnowlege_BP_Implementation(int32 Index)
{
    UE_LOG(LogTemp, Display, TEXT("slide: %i"), Index);
}

void URSLibraryWidget::OnNextKnowlege()
{
    if (FoundKnowledges.Num() == 0) return;
    
    const auto NextIndex = ++CurrentKnowlegeIndex % FoundKnowledges.Num();
    ShowCurrentKnowlege(NextIndex);
}

void URSLibraryWidget::OnPrevKnowlege()
{
    if (FoundKnowledges.Num() == 0) return;

    --CurrentKnowlegeIndex;
    if (CurrentKnowlegeIndex < 0)
    {
        CurrentKnowlegeIndex = FoundKnowledges.Num() - 1;
    }
    const auto NextIndex = CurrentKnowlegeIndex % FoundKnowledges.Num();
    ShowCurrentKnowlege(NextIndex);
}

void URSLibraryWidget::ShowCurrentKnowlege(int32 Index)
{
    if (!FoundKnowledges.IsValidIndex(Index)) return;
    CurrentKnowlegeIndex = Index;
    UE_LOG(LogTemp, Display, TEXT("slide %i"), Index);

    for (auto& Knowlege : FoundKnowledges)
    {
        Knowlege.bIsActive = false;
    }
    CurrentKnowlege = FoundKnowledges[Index];
    CurrentKnowlege.bIsActive = true;

    OnShowCurrentKnowlege_BP(Index);
}

