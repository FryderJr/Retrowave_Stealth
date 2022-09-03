// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RSInteractableActor.generated.h"

UCLASS()
class RETROWAVE_STEALTH_API ARSInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ARSInteractableActor();

    virtual void InteractWithObject(APlayerController* PC);

protected:
	virtual void BeginPlay() override;
};
