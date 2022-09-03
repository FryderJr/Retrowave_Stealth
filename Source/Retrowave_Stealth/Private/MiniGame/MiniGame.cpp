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

void UMiniGame::PaintAll(const FColor& Color)
{
	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();
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
	PlaceKeyword();
}

void UMiniGame::RandomizeMatrix()
{
	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();
    if (MatrixRows.Num() == 0) return;
    
	RowsLength = MatrixRows.Num();
	for (uint8 i = 0; i < MatrixRows.Num(); i++)
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
	if (X < 0 || Y < 0) return;

	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();

	if (MatrixRows.Num() == 0 || RowsLength < 1 || Y + 1 > RowsLength) return;

	const auto MatrixColumnContainer = Cast<UColumn>(MatrixRows[Y]);
    if (!MatrixColumnContainer) return;

	TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();

	if (ColumnsLength < 1 || X + KeywordLength > ColumnsLength) return;
    
    PaintAll(FColor::Black);
    
    PaintRowCellsInRange(MatrixColumns, X, KeywordLength, FColor::White);

	CurrentColumn = X;
	CurrentRow = Y;
}

void UMiniGame::PlaceKeyword()
{
    KeywordBeginsAtRow = FMath::RandRange(0, RowsLength - 1);
    KeywordBeginsAtColumn = FMath::RandRange(0, ColumnsLength - KeywordLength);
    
	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();
    if (MatrixRows.Num() == 0) return;
    
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
    return bIsValidField;
}

void UMiniGame::Blink()
{
	RandomizeMatrix();
    PlaceKeyword();
}

void UMiniGame::StartBlinking()
{
	FTimerDelegate CustomDelegate;
	CustomDelegate.BindUFunction(this, FName("Blink"));
	GetWorld()->GetTimerManager().SetTimer(FBlinkTimer, CustomDelegate, BlinkingTime, true);
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
