// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RSTypes.h"
#include "RSPlayerHUD.generated.h"

UCLASS()
class SYNCHRO_API ARSPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
    UUserWidget* GetCurrentWidget() const { return CurrentWidget; };
	
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> PlayerWidgetClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> InteractionWidgetClass;
    
    virtual void BeginPlay() override;
    
private:
    UPROPERTY()
    TMap<ERSGameState, UUserWidget*> GameWidgets;
    
    UPROPERTY()
    UUserWidget* CurrentWidget;
    
    void OnGameStateChanged(ERSGameState State);
};
