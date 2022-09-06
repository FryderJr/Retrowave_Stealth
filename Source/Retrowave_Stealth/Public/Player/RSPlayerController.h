// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RSTypes.h"
#include "RSPlayerController.generated.h"

class ACameraActor;

UCLASS()
class RETROWAVE_STEALTH_API ARSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0.0f))
    float CameraBlendTime;

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;
    
private:
    void OnGamePaused();
    void OnGameStateChanged(ERSGameState State);

    void OnInteractionStart(ACameraActor* Camera);
    void OnInteractionStop();
};
