// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable/RSInteractableActor.h"
#include "RSTerminal.generated.h"

class UBoxComponent;
class UWidgetComponent;
class ACameraActor;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionStartSignature, ACameraActor*);
DECLARE_MULTICAST_DELEGATE(FOnInteractionStopSignature);

UCLASS()
class RETROWAVE_STEALTH_API ARSTerminal : public ARSInteractableActor
{
	GENERATED_BODY()
	
public:	
	ARSTerminal();

    virtual void Tick(float DeltaSeconds);

    FOnInteractionStartSignature OnInteractionStart;
    FOnInteractionStopSignature OnInteractionStop;

    bool GetHackedStatus() const { return bIsHackedSucces; };
    bool GetWorkingStatus() const { return bIsActive; };

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
    USceneComponent* SceneComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
    UStaticMeshComponent* TerminalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
    UBoxComponent* TriggerComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
    ACameraActor* TerminalCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* MiniGameComponent;

	virtual void BeginPlay() override;
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    virtual void InteractWithObject() override;

    virtual void OnActorLoaded_Implementation() override;

private:
    UPROPERTY(SaveGame)
    bool bIsActive{true};

    UPROPERTY(SaveGame)
    bool bIsHackedSucces{false};

    bool bInFocus{false};

private:
    void OnCheckField(bool bIsValidField);

    void OnQuitTerminal();
};
