// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSInteractionWidget.generated.h"

class UHorizontalBox;
class UMiniGame;

UCLASS()
class RETROWAVE_STEALTH_API URSInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void InitMiniGame();
	
protected:
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* MiniGameBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MiniGameWidgetClass;

    virtual void NativeOnInitialized() override;
};
