// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSInteractionWidget.generated.h"

class UHorizontalBox;
class UMiniGame;

UCLASS()
class SYNCHRO_API URSInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void InitMiniGame();
	
protected:
    //UPROPERTY(meta = (BindWidget))
    //UHorizontalBox* MiniGameBox;

    //UPROPERTY(meta = (BindWidget))
    //UHorizontalBox* TutorialBox;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    //TSubclassOf<UUserWidget> MiniGameWidgetClass;

    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    //TSubclassOf<UUserWidget> TutorialWidgetClass;

    virtual void NativeOnInitialized() override;
};
