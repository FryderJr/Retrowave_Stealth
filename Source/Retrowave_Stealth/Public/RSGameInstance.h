// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RSGameInstance.generated.h"

UCLASS()
class RETROWAVE_STEALTH_API URSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    FName GetStartupLevelName() const { return StartupLevelName; };
    FName GetMenuLevelName() const { return MenuLevelName; };
    FString GetSaveSlotName() const { return SaveSlotName; };

    UFUNCTION(BlueprintCallable, Category = "Game")
    void SaveGame(FTransform PlayerTransform);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadGame();

    UFUNCTION()
    void SavedGame(const FString& SlotName, const int32 UserIndex, bool bSuccess);
    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(VisibleAnywhere, Category = "Game")
    FString SaveSlotName = "GameSaveSlot";
    
    UPROPERTY(VisibleAnywhere, Category = "Game")
    FTransform PlayerLocation;
};
