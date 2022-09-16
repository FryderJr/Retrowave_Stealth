// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RSActorSave.h"
#include "GameFramework/Actor.h"
#include "RSInteractableActor.generated.h"

UCLASS()
class SYNCHRO_API ARSInteractableActor : public AActor, public IRSActorSave
{
	GENERATED_BODY()
	
public:	
	ARSInteractableActor();

    virtual void Tick(float DeltaSeconds) { Super::Tick(DeltaSeconds); };

    virtual void InteractWithObject() {};

	virtual void StopInteractWithObject() {};

    virtual void OnActorLoaded_Implementation() { UE_LOG(LogTemp, Display, TEXT("ARSInteractableActor OnActorLoaded")); };

protected:
	virtual void BeginPlay() override;
};
