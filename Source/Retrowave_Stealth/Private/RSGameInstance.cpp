// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameInstance.h"
#include "RSSaveGame.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable/RSTerminal.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void URSGameInstance::Init()
{
    Super::Init();
}

void URSGameInstance::SaveGame(FTransform PlayerTransform)
{
    //if (URSSaveGame* SaveGameInstance = Cast<URSSaveGame>(UGameplayStatics::CreateSaveGameObject(URSSaveGame::StaticClass())))
    //{
        // Set up the (optional) delegate.
        FAsyncSaveGameToSlotDelegate SavedDelegate;
        // USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
        SavedDelegate.BindUObject(this, &URSGameInstance::SavedGame);

        // Set data on the savegame object.
        //SaveGameInstance->PlayerTransform = PlayerTransform;
        CurrentSaveGame->PlayerTransform = PlayerTransform;

        // Start async save process.
        //UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveSlotName, 0, SavedDelegate);
        UGameplayStatics::AsyncSaveGameToSlot(CurrentSaveGame, SaveSlotName, 0, SavedDelegate);
    //}
}

void URSGameInstance::SavedGame(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{

}

void URSGameInstance::SaveTerminalData()
{
    if (!CurrentSaveGame) return;   //checknoentry
    UE_LOG(LogTemp, Display, TEXT("URSGameInstance: SaveTerminalData"));
    CurrentSaveGame->SavedActors.Empty();

    for (FActorIterator It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        // Only interested in our 'gameplay actors', skip actors that are being destroyed
        // Note: You might instead use a dedicated SavableObject interface for Actors you want to save instead of re-using GameplayInterface
        if (!IsValid(Actor) || !Actor->Implements<ARSTerminal>()) continue;

        FActorSaveData ActorData;
        ActorData.ActorName = Actor->GetFName();
        ActorData.Transform = Actor->GetActorTransform();

        // Pass the array to fill with data from Actor
        FMemoryWriter MemWriter(ActorData.ByteData);

        FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
        // Find only variables with UPROPERTY(SaveGame)
        Ar.ArIsSaveGame = true;
        // Converts Actor's SaveGame UPROPERTIES into binary array
        Actor->Serialize(Ar);

        CurrentSaveGame->SavedActors.Add(ActorData);
    }

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, 0);
}


void URSGameInstance::LoadGame()
{
    CurrentSaveGame = Cast<URSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
    if (!CurrentSaveGame) return;
    UE_LOG(LogTemp, Display, TEXT("URSGameInstance: LoadGame"));
    //if (URSSaveGame* LoadedGame = Cast<URSSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0)))
    //{
    for (FActorIterator It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Cast<APlayerStart>(Actor))
        {
            //It->SetActorTransform(LoadedGame->PlayerTransform);
            It->SetActorTransform(CurrentSaveGame->PlayerTransform);
        }
        if (Cast<ARSTerminal>(Actor))
        {
            for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
            {
                if (ActorData.ActorName == Actor->GetFName())
                {
                    //Actor->SetActorTransform(ActorData.Transform);
                    FTransform NewTransform = FTransform(ActorData.Transform.GetRotation(), ActorData.Transform.GetLocation(), FVector(3.f));
                    Actor->SetActorTransform(NewTransform);

                    FMemoryReader MemReader(ActorData.ByteData);

                    FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
                    Ar.ArIsSaveGame = true;
                    // Convert binary array back into actor's variables
                    Actor->Serialize(Ar);

                    //ISGameplayInterface::Execute_OnActorLoaded(Actor);

                    break;
                }
            }
        }
    }
        //GetPrimaryPlayerController()->GetPawn()->SetActorTransform(LoadedGame->PlayerTransform);
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
    //UE_LOG(LogTemp, Warning, TEXT("LOADED: (%f, %f, %f)"), LoadedGame->PlayerTransform.GetLocation().X, LoadedGame->PlayerTransform.GetLocation().Y, LoadedGame->PlayerTransform.GetLocation().Z);
    //}
}
