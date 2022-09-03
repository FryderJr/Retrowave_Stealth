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


