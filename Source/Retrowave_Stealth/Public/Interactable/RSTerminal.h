// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSTerminal.generated.h"

class UBoxComponent;


UCLASS()
class RETROWAVE_STEALTH_API ARSTerminal : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSTerminal();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
    USceneComponent* SceneComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
    UStaticMeshComponent* TerminalMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
    UBoxComponent* TriggerComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
    ACameraActor* TerminalCamera;

	virtual void BeginPlay() override;
    
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:
    bool bIsActive{true};
};
