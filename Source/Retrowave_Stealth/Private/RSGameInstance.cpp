// Fill out your copyright notice in the Description page of Project Settings.


#include "RSGameInstance.h"
#include "RSActorSave.h"
#include "RSSaveGame.h"
#include "RSEndSaveGame.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void URSGameInstance::Init()
{
    Super::Init();
}

void URSGameInstance::SetInfoPoints(int32 Points)
{
    InfoPoints = Points;
}

void URSGameInstance::SaveGame(FTransform PlayerTransform)
{
    if (URSSaveGame* SaveGameInstance = Cast<URSSaveGame>(UGameplayStatics::CreateSaveGameObject(URSSaveGame::StaticClass())))
    {
        SaveGameInstance->SavedActors.Empty();
        // Set up the (optional) delegate.
        FAsyncSaveGameToSlotDelegate SavedDelegate;
        // USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
        SavedDelegate.BindUObject(this, &URSGameInstance::SavedGame);

        for (FActorIterator It(GetWorld()); It; ++It)
        {
            AActor* Actor = *It;
            // Only interested in our 'gameplay actors', skip actors that are being destroyed
            // Note: You might instead use a dedicated SavableObject interface for Actors you want to save instead of re-using GameplayInterface
            if (Actor->IsPendingKill() || !Actor->Implements<URSActorSave>()) continue;
            
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

            SaveGameInstance->SavedActors.Add(ActorData);
        }

        // Set data on the savegame object.
        SaveGameInstance->PlayerTransform = PlayerTransform;

        // Start async save process.
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, 0);
    }
}

void URSGameInstance::SaveEndGameState()
{
    if (URSEndSaveGame* SaveGameInstance = Cast<URSEndSaveGame>(UGameplayStatics::CreateSaveGameObject(URSEndSaveGame::StaticClass())))
    {
        SaveGameInstance->TerminalPoints = InfoPoints;
        bool bGameSaved = UGameplayStatics::SaveGameToSlot(SaveGameInstance, EndGameSaveSlotName, 0);
        UGameplayStatics::OpenLevel(GetWorld(), GetMenuLevelName(), true);
    }
}

void URSGameInstance::LoadEndGameState()
{
    if (URSEndSaveGame* LoadedGame = Cast<URSEndSaveGame>(UGameplayStatics::LoadGameFromSlot(EndGameSaveSlotName, 0)))
    {
        if (LoadedGame->TerminalPoints > InfoPoints)
        {
            InfoPoints = LoadedGame->TerminalPoints;
        }
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
	        if (Cast<APlayerStart>(Actor))
	        {
            	It->SetActorTransform(LoadedGame->PlayerTransform);
        	}

            if (Actor->Implements<URSActorSave>())
            {
                for (FActorSaveData ActorData : LoadedGame->SavedActors)
                {
                    if (ActorData.ActorName == Actor->GetFName())
                    {
                        UE_LOG(LogTemp, Display, TEXT("URSGameInstance: LoadTerminalData %s"), *Actor->GetName());

                        Actor->SetActorTransform(ActorData.Transform);

                        FMemoryReader MemReader(ActorData.ByteData);

                        FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
                        Ar.ArIsSaveGame = true;
                        // Convert binary array back into actor's variables
                        Actor->Serialize(Ar);

                        IRSActorSave::Execute_OnActorLoaded(Actor);

                        break;
                    }
                }
            }
        }
        //GetPrimaryPlayerController()->GetPawn()->SetActorTransform(LoadedGame->PlayerTransform);
        // The operation was successful, so LoadedGame now contains the data we saved earlier.
    UE_LOG(LogTemp, Warning, TEXT("LOADED: (%f, %f, %f)"), LoadedGame->PlayerTransform.GetLocation().X, LoadedGame->PlayerTransform.GetLocation().Y, LoadedGame->PlayerTransform.GetLocation().Z);
    }
}
