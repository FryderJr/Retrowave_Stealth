// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RSTypes.h"
#include "RSGameMode.generated.h"


UCLASS()
class SYNCHRO_API ARSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    ARSGameMode();
    
    FOnGameStateChagedSignature OnGameStateChanged;

    UFUNCTION(BlueprintCallable)
    void InteractWithObject();

    UFUNCTION(BlueprintCallable)
    void StopInteraction();

    void UpdateTerminalData();

    UFUNCTION(BlueprintImplementableEvent, Category = Game)
    void PlayerStatusChanged(int32 SpottedNum, int32 AlertedNum);

    UFUNCTION(BlueprintCallable, Category = Game)
    void AddSpottedBy(AActor* Enemy);

    UFUNCTION(BlueprintCallable, Category = Game)
    void AddAlertedBy(AActor* Enemy);

    UFUNCTION(BlueprintCallable, Category = Game)
    void DeleteSpottedBy(AActor* Enemy);

    UFUNCTION(BlueprintCallable, Category = Game)
    void DeleteAlertedBy(AActor* Enemy);

    UFUNCTION(BlueprintCallable, Category = Game)
    int32 GetSpottedByNum();

    UFUNCTION(BlueprintCallable, Category = Game)
    int32 GetAlertedByNum();

    UFUNCTION(BlueprintCallable, Category = "UI")
    FTerminalData GetCurrentTerminalData() const { return CurrentTerminalData; };
    
protected:
    virtual void StartPlay() override;
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    
private:
    ERSGameState RetrowaveGameState = ERSGameState::WaitingToStart;

    FTerminalData CurrentTerminalData;

    TArray<AActor*> PlayerSpottedBy = {};

    TArray<AActor*> PlayerAlertedBy = {};
    
    void InitTerminals();
    void SetGameState(ERSGameState State);

    void OnInteractionStart(ACameraActor* Camera);
    void OnInteractionStop();
};
