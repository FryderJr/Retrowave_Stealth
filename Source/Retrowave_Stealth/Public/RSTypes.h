//  Retrowave_Stealth

#pragma once

#include "RSTypes.generated.h"

UENUM(BlueprintType)
enum class ERSGameState : uint8
{
    WaitingToStart = 0,
    InProgress,
    Interact,
    Pause,
    GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChagedSignature, ERSGameState);

USTRUCT(BlueprintType)
struct FTerminalData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Info")
    int32 TerminalsNum{0};
    UPROPERTY(BlueprintReadWrite, Category = "Info")
    int32 ActiveTerminalsNum{0};
    UPROPERTY(BlueprintReadWrite, Category = "Info")
    int32 HackedSuccesTerminalsNum{0};
};


