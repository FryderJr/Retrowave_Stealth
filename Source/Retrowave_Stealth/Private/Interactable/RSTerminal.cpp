// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/RSTerminal.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RSBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "RSGameMode.h"

ARSTerminal::ARSTerminal()
{
	PrimaryActorTick.bCanEverTick = false;
    
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);

    TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>("TerminalMesh");
    TerminalMesh->SetupAttachment(GetRootComponent());

    TriggerComponent = CreateDefaultSubobject<UBoxComponent>("TriggerComponent");
    TriggerComponent->SetupAttachment(GetRootComponent());
    TriggerComponent->SetBoxExtent(FVector(100.f));
    
    TerminalCamera = CreateDefaultSubobject<ACameraActor>("TerminalCamera");
}

void ARSTerminal::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARSTerminal::NotifyActorBeginOverlap(AActor* OtherActor)
{
    if (!bIsActive) return;
    
    const auto Player = Cast<ARSBaseCharacter>(OtherActor);
    if (!Player) return;

    Player->SetCurrentInteractableObject(this);
}

void ARSTerminal::NotifyActorEndOverlap(AActor* OtherActor)
{
    const auto Player = Cast<ARSBaseCharacter>(OtherActor);
    if (!Player) return;

    Player->SetCurrentInteractableObject(nullptr);
}

void ARSTerminal::InteractWithObject(APlayerController* PC)
{
    if (!PC) return;
    PC->SetViewTargetWithBlend(TerminalCamera, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);

    if (!GetWorld() || !GetWorld()->GetAuthGameMode<ARSGameMode>()) return;
    GetWorld()->GetAuthGameMode<ARSGameMode>()->PlayMiniGame();
}


