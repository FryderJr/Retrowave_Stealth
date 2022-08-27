// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Row.h"
#include "Blueprint/UserWidget.h"
#include "MiniGame.generated.h"

/**
 * 
 */
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
	int FieldLength = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
	FString Field = "";

	TArray<TCHAR> Code;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MiniGame)
	int CurrentRow = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MiniGame)
	int CurrentColumn = 0;

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void PaintAll();

	FString RandomChar();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void RandomizeField();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void RandomizeMatrix();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void MoveField(int X, int Y);

	void PlaceField();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	bool CheckField();

	UFUNCTION()
	void Blink();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void StartBlinking();

private:

	size_t FieldRow = 0;
	size_t FieldColumn = 0;

	size_t ColumnsLength = 0;
	size_t RowsLength = 0;

	FTimerHandle FBlinkTimer;
};
