// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSGamePauseWidget.generated.h"

class UButton;

UCLASS()
class RETROWAVE_STEALTH_API URSGamePauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeOnInitialized() override;
    
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;
    
private:
    UFUNCTION()
    void OnClearPause();
};
