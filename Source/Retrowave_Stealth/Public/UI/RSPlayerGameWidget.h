// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSTypes.h"
#include "RSPlayerGameWidget.generated.h"

UCLASS()
class RETROWAVE_STEALTH_API URSPlayerGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
    UFUNCTION(BlueprintCallable)
    bool NextPharese();

    UFUNCTION(BlueprintCallable)
    FDialogData GetCurrentPhrase() const { return CurrentPhrase; };

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialog")
    TArray<FDialogData> Dialog;

    virtual void NativeOnInitialized() override;

private:
    FDialogData CurrentPhrase;
    int32 CurrentPhraseIndex;

    void StartDialog(uint32 PhreseNumber);
};
