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

USTRUCT(BlueprintType)
struct FDialogData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog")
    FText Nickname;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dialog")
    FText Expression;
};

USTRUCT(BlueprintType)
struct FActorSaveData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
    FName ActorName;
    /* For movable Actors, keep location,rotation,scale. */
    UPROPERTY()
    FTransform Transform;
    /* Contains all 'SaveGame' marked variables of the Actor */
    UPROPERTY()
    TArray<uint8> ByteData;
};

USTRUCT(BlueprintType)
struct FPlayerSaveData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
    FName ActorName;

    UPROPERTY()
    TArray<uint8> ByteData;
};