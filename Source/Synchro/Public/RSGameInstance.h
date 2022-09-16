// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RSGameInstance.generated.h"

// rebase to UGameInstanceSubsystem
class URSSaveGame;
//=====

UCLASS()
class SYNCHRO_API URSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleDefaultsOnly, Category = "Tutorial")
    bool bIsTutorial{true};

    virtual void Init() override;
    
    FName GetStartupLevelName() const { return StartupLevelName; };
    FName GetMenuLevelName() const { return MenuLevelName; };

    UFUNCTION(BlueprintCallable, Category = "Game")
    float GetMusicVolume() const { return PercentMusicVolume; };

    UFUNCTION(BlueprintCallable, Category = "Game")
    float GetSfxVolume() const { return PercentSfxVolume; };

    UFUNCTION(BlueprintCallable, Category = "Game")
    void SetMusicVolume(float MusicVolume);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void SetSfxVolume(float SfxVolume);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game")
    void OnSetMusicVolume(float MusicVolume);

    UFUNCTION(BlueprintImplementableEvent, Category = "Game")
    void OnSetSfxVolume(float SfxVolume);

    UFUNCTION(BlueprintCallable, Category = "Game")
    FString GetSaveSlotName() const { return SaveSlotName; };

    UFUNCTION(BlueprintCallable, Category = "Score")
    int32 GetInfoPoints() const { return InfoPoints; };

    UFUNCTION(BlueprintCallable, Category = "Score")
    void SetInfoPoints(int32 Points);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void SaveGame(FTransform PlayerTransform);

    /*
    * will be called from the BP_Goal
    */
    UFUNCTION(BlueprintCallable, Category = "Score")
    void SaveEndGameState();

    /*
    * will be called from Menu Level Blueprint
    */
    UFUNCTION(BlueprintCallable, Category = "Score")
    void LoadEndGameState();

    UFUNCTION()
    void SavedGame(const FString& SlotName, const int32 UserIndex, bool bSuccess);

    UFUNCTION(BlueprintCallable, Category = "Game")
    void LoadGame();
    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    // rebase to UGameInstanceSubsystem
    UPROPERTY(VisibleAnywhere, Category = "Game")
    FString SaveSlotName = "GameSaveSlot";
    //=====

    UPROPERTY(VisibleAnywhere, Category = "Score")
    FString EndGameSaveSlotName = "EndGameSlot";

    UPROPERTY(VisibleAnywhere, Category = "Game")
    FTransform PlayerLocation;

    UPROPERTY(VisibleAnywhere, Category = "Score")
    int32 InfoPoints{0};

    float PercentMusicVolume = 0.8f;

    float PercentSfxVolume = 0.8f;
private:
    // rebase to UGameInstanceSubsystem
    UPROPERTY()
    URSSaveGame* CurrentSaveGame;
    //=====
};
