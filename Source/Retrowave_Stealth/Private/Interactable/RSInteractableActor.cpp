// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/RSInteractableActor.h"

ARSInteractableActor::ARSInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ARSInteractableActor::InteractWithObject(APlayerController* PC)
{
}

void ARSInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

