// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Row.h"
#include "Blueprint/UserWidget.h"
#include "MiniGame.generated.h"

UCLASS()
class RETROWAVE_STEALTH_API UMiniGame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MatrixCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URow* Matrix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
	int KeywordLength = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
	FString Keyword = "";

	//TArray<TCHAR> Code;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MiniGame)
	int CurrentRow = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MiniGame)
	int CurrentColumn = 0;

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void PaintAll();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void CreateKeyword();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void RandomizeMatrix();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void MoveField(int X, int Y);

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	bool CheckField();

	UFUNCTION()
	void Blink();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void StartBlinking();

private:
    const FString SymbolsToFill = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890`-=],./~!@#$%^&*()_+{}|:<>?";
    
	size_t KeywordBeginsAtRow = 0;
	size_t KeywordBeginsAtColumn = 0;

	size_t ColumnsLength = 0;
	size_t RowsLength = 0;

	FTimerHandle FBlinkTimer;
    
    FString RandomChar();
    
    void PlaceKeyword();
    
    void PaintRowCellsInRange(TArray<UWidget*>& CellsInRow, const uint32 Begin, const uint32 Range, const FColor& Color);
};
