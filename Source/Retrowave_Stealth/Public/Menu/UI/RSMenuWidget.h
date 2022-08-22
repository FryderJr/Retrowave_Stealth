// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSMenuWidget.generated.h"

class UButton;

UCLASS()
class RETROWAVE_STEALTH_API URSMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartPlayButton;
    
    virtual void NativeOnInitialized() override;
    
private:
    UFUNCTION()
    void OnStartPlay();
};
