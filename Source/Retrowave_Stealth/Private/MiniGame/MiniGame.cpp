// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGame/MiniGame.h"
#include "MiniGame/Column.h"
#include "MiniGame/Cell.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Styling/SlateColor.h"
#include "Math/Color.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void UMiniGame::PaintAll()
{
	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();

	for (size_t i = 0; i < MatrixRows.Num(); i++)
	{
		UColumn* MatrixColumnContainer = Cast<UColumn>(MatrixRows[i]);
		TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();
		for (size_t j = 0; j < MatrixColumns.Num(); j++)
		{
			UCell* MatrixCell = Cast<UCell>(MatrixColumns[j]);
			FSlateBrush NewBrush = FSlateBrush(MatrixCell->Background->Brush);
			NewBrush.TintColor = FSlateColor(FLinearColor(FColor::Black));
			MatrixCell->Background->SetBrush(NewBrush);
		}
	}
}

FString UMiniGame::RandomChar()
{
	FString vaild = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890`-=]’,./~!@#$%^&*()_+{}|:<>?";
	FString rtnStr = (&vaild.GetCharArray()[FMath::RandRange(0, vaild.Len() - 1)]);
	return FString(1, &rtnStr[0]);
}

void UMiniGame::RandomizeField()
{
	for (size_t i = 0; i < FieldLength; i++)
	{
		Field += RandomChar();
	}
	FieldRow = FMath::RandRange(0, RowsLength - 1);
	FieldColumn = FMath::RandRange(0, ColumnsLength - FieldLength);
	PlaceField();
}

void UMiniGame::RandomizeMatrix()
{
	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();
	RowsLength = MatrixRows.Num();
	for (size_t i = 0; i < MatrixRows.Num(); i++)
	{
		UColumn* MatrixColumnContainer = Cast<UColumn>(MatrixRows[i]);
		TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();
		ColumnsLength = MatrixColumns.Num();
		for (size_t j = 0; j < MatrixColumns.Num(); j++)
		{
			UCell* MatrixCell = Cast<UCell>(MatrixColumns[j]);
			MatrixCell->CellText->SetText(FText::FromString(RandomChar()));
		}
	}
}

void UMiniGame::MoveField(int X, int Y)
{
	if (X < 0)
	{
		return;
	}

	if (Y < 0)
	{
		return;
	}

	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();

	if (RowsLength < 1)
	{
		return;
	}

	if (Y + 1 > RowsLength)
	{
		return;
	}

	UColumn* MatrixColumnContainer = Cast<UColumn>(MatrixRows[Y]);

	TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();

	if (ColumnsLength < 1)
	{
		return;
	}

	if (X + FieldLength > ColumnsLength)
	{
		return;
	}

	PaintAll();

	for (size_t i = X; i < X + FieldLength; i++)
	{
		UCell* MatrixCell = Cast<UCell>(MatrixColumns[i]);
		FSlateBrush NewBrush = FSlateBrush(MatrixCell->Background->Brush);
		NewBrush.TintColor = FSlateColor(FLinearColor(FColor::White));
		MatrixCell->Background->SetBrush(NewBrush);
	}

	CurrentColumn = X;
	CurrentRow = Y;
}

void UMiniGame::PlaceField()
{
	
	TArray<UWidget*> MatrixRows = Matrix->Rows->GetAllChildren();
	UColumn* MatrixColumnContainer = Cast<UColumn>(MatrixRows[FieldRow]);
	TArray<UWidget*> MatrixColumns = MatrixColumnContainer->Columns->GetAllChildren();
	for (size_t k = FieldColumn; k < FieldColumn + FieldLength; k++)
	{
		UCell* MatrixCell = Cast<UCell>(MatrixColumns[k]);
		MatrixCell->CellText->SetText(FText::FromString(FString(1, &Field[k - FieldColumn])));
	}
}

bool UMiniGame::CheckField()
{
	if (CurrentRow == FieldRow && CurrentColumn == FieldColumn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UMiniGame::Blink()
{
	RandomizeMatrix();
	PlaceField();
}

void UMiniGame::StartBlinking()
{
	FTimerDelegate CustomDelegate;
	CustomDelegate.BindUFunction(this, FName("Blink"));
	GetWorld()->GetTimerManager().SetTimer(FBlinkTimer, CustomDelegate, 0.5f, true);
}
