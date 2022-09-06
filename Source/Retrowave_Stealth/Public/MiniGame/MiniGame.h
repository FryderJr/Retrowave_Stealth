// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGame.generated.h"

class UCanvasPanel;
class UTextBlock;
class URow;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCheckFieldSignature, bool);
DECLARE_MULTICAST_DELEGATE(FOnQuitMiniGameSignature);

UCLASS()
class RETROWAVE_STEALTH_API UMiniGame : public UUserWidget
{
	GENERATED_BODY()

public:
    FOnCheckFieldSignature OnCheckField;
    FOnQuitMiniGameSignature OnQuitMiniGame;

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	void MoveField(int32 X, int32 Y);

	UFUNCTION(BlueprintCallable, Category = MiniGame)
	bool CheckField();
    
    UFUNCTION(BlueprintCallable, Category = MiniGame)
    void QuitMiniGame();

    void StartBlinking();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UCanvasPanel* MatrixCanvas;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    URow* Matrix;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KeywordToFind;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
    int KeywordLength = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniGame)
    float BlinkingRate = 4.f;
    
    virtual void NativeOnInitialized() override;

private:
    const FString SymbolsToFill = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890`-=][,./~!@#$%^&*()_+{}|:<>?";

    FString Keyword = "";

    int32 KeywordBeginsAtRow = 0;
    int32 KeywordBeginsAtColumn = 0;

    int32 ColumnsLength = 0;
    int32 RowsLength = 0;

    int32 CurrentRow = 0;
    int32 CurrentColumn = 0;

	FTimerHandle BlinkTimer;
    
    UPROPERTY()
    TArray<UWidget*> MatrixRows;

    void PaintAll(const FColor& Color);

    FString RandomChar();    

    void RandomizeMatrix();

    void CreateKeyword();

    void PlaceKeyword();
    
    void PaintRowCellsInRange(TArray<UWidget*>& CellsInRow, const uint32 Begin, const uint32 Range, const FColor& Color);
    
    void Blink();
};
