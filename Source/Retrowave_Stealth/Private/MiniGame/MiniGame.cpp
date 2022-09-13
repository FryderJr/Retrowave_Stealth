// Fill out your copyright notice in the Description page of Project Settings.

#include "MiniGame/MiniGame.h"
#include "MiniGame/Column.h"
#include "MiniGame/Cell.h"
#include "MiniGame/Row.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

bool UMiniGame::bIsTutorial = true;

void UMiniGame::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    InitSlides();

    MatrixRows = Matrix->Rows->GetAllChildren();
    RowsLength = MatrixRows.Num();
    RandomizeMatrix();
    MoveField(0,0);
    CreateKeyword();
    PlaceKeyword();
}

void UMiniGame::PaintAll(const FColor& Color)
{
    if (MatrixRows.Num() == 0) return;

    for (const auto& MatrixRow : MatrixRows)
    {
        const auto MatrixColumnsContainer = Cast<UColumn>(MatrixRow);
        if (!MatrixColumnsContainer) continue;

        TArray<UWidget*> MatrixColumns = MatrixColumnsContainer->Columns->GetAllChildren();
        PaintRowCellsInRange(MatrixColumns, 0, MatrixColumns.Num(), Color);
    }
}

FString UMiniGame::RandomChar()
{
    if (SymbolsToFill.Len() == 0) return FString(""); //checkNoEntry
    uint32 RandIndex = FMath::RandRange(0, SymbolsToFill.Len() - 1);
    return FString(1, &SymbolsToFill[RandIndex]);
}

void UMiniGame::CreateKeyword()
{
	for (uint8 i = 0; i < KeywordLength; i++)
	{
        Keyword += RandomChar();
	}
    if (KeywordToFind)
    {
        KeywordToFind->SetText(FText::FromString(Keyword));
    }
}

void UMiniGame::RandomizeMatrix()
{
    if (RowsLength == 0) return;
    
	for (uint8 i = 0; i < RowsLength; i++)
	{
		UColumn* MatrixColumnContainer = Cast<UColumn>(MatrixRows[i]);
        if (!MatrixColumnContainer) continue;
        
		TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();
        if (MatrixColumns.Num() == 0) continue;
        
		ColumnsLength = MatrixColumns.Num();

        for (const auto& Column : MatrixColumns)
        {
            const auto Cell = Cast<UCell>(Column);
            if (!Cell) return;
            
            Cell->CellText->SetText(FText::FromString(RandomChar()));
        }
	}
}

void UMiniGame::MoveField(int32 X, int32 Y)
{
    const auto ColumnToMove = CurrentColumn + X;
    const auto RowToMove = CurrentRow + Y;

    if (ColumnToMove > ColumnsLength - KeywordLength || 
        ColumnToMove < 0 ||
        RowToMove > RowsLength - 1 ||
        RowToMove < 0) return;

    const auto MatrixColumnContainer = Cast<UColumn>(MatrixRows[RowToMove]);
    if (!MatrixColumnContainer) return;

    TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();
    if (MatrixColumns.Num() == 0) return;

    PaintAll(FColor::Transparent);

    PaintRowCellsInRange(MatrixColumns, ColumnToMove, KeywordLength, FColor::White);

    CurrentColumn = ColumnToMove;
    CurrentRow = RowToMove;
}

void UMiniGame::PlaceKeyword()
{
    if (RowsLength == 0) return;

    KeywordBeginsAtRow = FMath::RandRange(0, RowsLength - 1);
    KeywordBeginsAtColumn = FMath::RandRange(0, ColumnsLength - KeywordLength);
    
    const auto MatrixColumnContainer = Cast<UColumn>(MatrixRows[KeywordBeginsAtRow]);
    if (!MatrixColumnContainer) return;
    
	TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();
    if (MatrixColumns.Num() == 0) return;
    
	for (uint8 i = KeywordBeginsAtColumn; i < KeywordBeginsAtColumn + KeywordLength; i++)
	{
		const auto MatrixCell = Cast<UCell>(MatrixColumns[i]);
        if (!MatrixCell) continue;
        
		MatrixCell->CellText->SetText(FText::FromString(FString(1, &Keyword[i - KeywordBeginsAtColumn])));
	}
}

bool UMiniGame::CheckField()
{
	bool bIsValidField = CurrentRow == KeywordBeginsAtRow && CurrentColumn == KeywordBeginsAtColumn;
    OnCheckField.Broadcast(bIsValidField);
    bIsValidField ? PaintAll(FColor::Green) : PaintAll(FColor::Red);
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(BlinkTimer);
    }
    return bIsValidField;
}

void UMiniGame::QuitMiniGame()
{
    OnQuitMiniGame.Broadcast();
}

void UMiniGame::ShowTutorial()
{
    UE_LOG(LogTemp, Display, TEXT("ShowTutorial: %s"), (bIsTutorial ? TEXT("true") : TEXT("false")));
    bIsTutorial ? PlayAnimation(TutorialAnimation) : PlayAnimationReverse(TutorialAnimation, 3.f);;
}

bool UMiniGame::NextTutorialSlide()
{
    if (TutorialSlides.Num() == 0) return false;

    const bool bIsFinished = CurrentSlideIndex == TutorialSlides.Num() - 1;

    if (!bIsFinished)
    {
        CurrentSlideIndex = ++CurrentSlideIndex % TutorialSlides.Num();
        CurrentTutorialSlide = TutorialSlides[CurrentSlideIndex];
    }
    else
    {
        PlayAnimationReverse(TutorialAnimation, 3.f);
        bIsTutorial = !bIsFinished;
    }
    UE_LOG(LogTemp, Display, TEXT("Tutorial: %s"), (bIsTutorial ? TEXT("true") : TEXT("false")));
    return bIsFinished;
}

void UMiniGame::StartBlinking()
{
    GetWorld()->GetTimerManager().SetTimer(BlinkTimer, this, &UMiniGame::Blink, BlinkingRate, true);
}

void UMiniGame::SetConditionAfterLoad(bool bIsHackSucces)
{
    UE_LOG(LogTemp, Display, TEXT("MiniGame hacked: %s"), (bIsHackSucces ? TEXT("true") : TEXT("false")));
    bIsHackSucces ? PaintAll(FColor::Green) : PaintAll(FColor::Red);
}

void UMiniGame::Blink()
{
	RandomizeMatrix();
    PlaceKeyword();
}

void UMiniGame::InitSlides()
{
    CurrentSlideIndex = 0;
    if (TutorialSlides.Num() == 0) return;
    CurrentTutorialSlide = TutorialSlides[CurrentSlideIndex];
}

void UMiniGame::PaintRowCellsInRange(TArray<UWidget*>& CellsInRow, const uint32 Begin, const uint32 Range, const FColor& Color)
{
    if (CellsInRow.Num() == 0 || Range == 0) return;
    
    for (uint8 i = Begin; i < Begin + Range; i++)
    {
        auto Cell = Cast<UCell>(CellsInRow[i]);
        if (!Cell) continue;
        
        FSlateBrush NewBrush = FSlateBrush(Cell->Background->Brush);
        NewBrush.TintColor = FSlateColor(FLinearColor(Color));
        Cell->Background->SetBrush(NewBrush);
    }
}
