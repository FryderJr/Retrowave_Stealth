// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGame.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCheckFieldSignature, bool);

UCLASS()
class RETROWAVE_STEALTH_API UMiniGame : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnCheckFieldSignature OnCheckField;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* MatrixCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URow* Matrix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
	int KeywordLength = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
	FString Keyword = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
    float BlinkingTime = 4.f;

    UPROPERTY(BlueprintReadWrite)
    int32 CurrentRow = 0;

    UPROPERTY(BlueprintReadWrite)
    int32 CurrentColumn = 0;

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void CreateKeyword();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void RandomizeMatrix();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void MoveField(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	bool CheckField();

	UFUNCTION()
	void Blink();

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void StartBlinking();

//protected:
    //virtual void NativeOnInitialized() override;

private:
    const FString SymbolsToFill = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890`-=][,./~!@#$%^&*()_+{}|:<>?";

    int32 KeywordBeginsAtRow = 0;
    int32 KeywordBeginsAtColumn = 0;

    int32 ColumnsLength = 0;
    int32 RowsLength = 0;

	FTimerHandle FBlinkTimer;
    
    void PaintAll(const FColor& Color);

    FString RandomChar();    

    void PlaceKeyword();
    
    void PaintRowCellsInRange(TArray<UWidget*>& CellsInRow, const uint32 Begin, const uint32 Range, const FColor& Color);
};
