// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameInstance.h"
#include "RSSaveGame.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void URSGameInstance::Init()
{
    Super::Init();
}

void URSGameInstance::SaveGame(FTransform PlayerTransform)
{
    if (URSSaveGame* SaveGameInstance = Cast<URSSaveGame>(UGameplayStatics::CreateSaveGameObject(URSSaveGame::StaticClass())))
    {
        // Set up the (optional) delegate.
        FAsyncSaveGameToSlotDelegate SavedDelegate;
        // USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
        SavedDelegate.BindUObject(this, &URSGameInstance::SavedGame);

        // Set data on the savegame object.
        SaveGameInstance->PlayerTransform = PlayerTransform;

        // Start async save process.
        UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveSlotName, 0, SavedDelegate);
    }
}

void URSGameInstance::SavedGame(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{

}

void URSGameInstance::LoadGame()
{
    if (URSSaveGame* LoadedGame = Cast<URSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0)))
    {
        for (FActorIterator It(GetWorld()); It; ++It)
        {
            AActor* Actor = *It;
            if (!Cast<APlayerStart>(Actor)) continue;
               
            It->SetActorTransform(LoadedGame->PlayerTransform);
        }
        //GetPrimaryPlayerController()->GetPawn()->SetActorTransform(LoadedGame->PlayerTransform);
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
        UE_LOG(LogTemp, Warning, TEXT("LOADED: (%f, %f, %f)"), LoadedGame->PlayerTransform.GetLocation().X, LoadedGame->PlayerTransform.GetLocation().Y, LoadedGame->PlayerTransform.GetLocation().Z);
    }
}
