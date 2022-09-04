// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable/RSInteractableActor.h"
#include "RSTerminal.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class RETROWAVE_STEALTH_API ARSTerminal : public ARSInteractableActor
{
	GENERATED_BODY()
	
public:	
	ARSTerminal();

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

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0.0f))
    float CameraBlendTime;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* MiniGameComponent;

	virtual void BeginPlay() override;
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

    virtual void InteractWithObject(ACharacter* Interactor) override;
    virtual void StopInteraction(ACharacter* Interactor) override;

private:
    bool bIsActive{true};
    bool bIsHackedSucces{false};

    void OnCheckField(bool bIsValidField);
};
