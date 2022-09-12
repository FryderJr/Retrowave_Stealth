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

    OpenedKnowleges ? 
        CurrentKnowlege = FoundKnowledges[CurrentKnowlegeIndex] :
        CurrentKnowlege = DefaultImage;

    if (NextKnowlegeButton)
    {
        NextKnowlegeButton->OnClicked.AddDynamic(this, &URSLibraryWidget::OnNextKnowlege);
    }
}

void URSLibraryWidget::GetKnowlegesInfo(int32& KnowlegeIndex, int32& TotalKnowlegesCount) const
{
    KnowlegeIndex = CurrentKnowlegeIndex + 1;
    TotalKnowlegesCount = FoundKnowledges.Num();
}

void URSLibraryWidget::OnNextKnowlege()
{
    if (FoundKnowledges.Num() == 0) return;
    
    const auto NextIndex = ++CurrentKnowlegeIndex % FoundKnowledges.Num();
    UE_LOG(LogTemp, Display, TEXT("Next"));
    ShowCurrentKnowlege(NextIndex);
}

void URSLibraryWidget::ShowCurrentKnowlege(int32 Index)
{
    if (!FoundKnowledges.IsValidIndex(Index)) return;
    CurrentKnowlegeIndex = Index;
    UE_LOG(LogTemp, Display, TEXT("slide %i"), Index);

    Index < OpenedKnowleges ? 
        CurrentKnowlege = FoundKnowledges[Index] :
        CurrentKnowlege = DefaultImage;
}
