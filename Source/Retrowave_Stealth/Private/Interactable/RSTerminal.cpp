// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable/RSTerminal.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Player/RSBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"
#include "MiniGame/MiniGame.h"

bool ARSTerminal::bIsTipActive = false;

ARSTerminal::ARSTerminal()
{
	PrimaryActorTick.bCanEverTick = true;
    
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);

    TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>("TerminalMesh");
    TerminalMesh->SetupAttachment(GetRootComponent());

    TriggerComponent = CreateDefaultSubobject<UBoxComponent>("TriggerComponent");
    TriggerComponent->SetupAttachment(GetRootComponent());
    TriggerComponent->SetBoxExtent(FVector(100.f));
    
    TerminalCamera = CreateDefaultSubobject<ACameraActor>("TerminalCamera");

    MiniGameComponent = CreateDefaultSubobject<UWidgetComponent>("MiniGameComonent");
    MiniGameComponent->SetupAttachment(GetRootComponent());
    MiniGameComponent->SetWidgetSpace(EWidgetSpace::World);
}

void ARSTerminal::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bInFocus && !bIsTipActive)
    {
        if (const auto MiniGameWidget = Cast<UMiniGame>(MiniGameComponent->GetUserWidgetObject()))
        {
            MiniGameWidget->SetFocus();
        }
    }
}

void ARSTerminal::BeginPlay()
{
	Super::BeginPlay();

    const auto MiniGameWidget = Cast<UMiniGame>(MiniGameComponent->GetUserWidgetObject());
    if (MiniGameWidget)
    {
        MiniGameWidget->bIsFocusable = true;
        MiniGameWidget->OnCheckField.AddUObject(this, &ARSTerminal::OnCheckField);
        MiniGameWidget->OnQuitMiniGame.AddUObject(this, &ARSTerminal::OnQuitTerminal);
    }
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

void ARSTerminal::InteractWithObject()
{
    if (!bIsActive) return;

    OnInteractionStart.Broadcast(TerminalCamera);

    bInFocus = true;

    const auto MiniGameWidget = Cast<UMiniGame>(MiniGameComponent->GetUserWidgetObject());
    if (MiniGameWidget)
    {
        MiniGameWidget->StartBlinking();
    }
}

void ARSTerminal::OnCheckField(bool bIsValidField)
{
    bIsActive = false;
    bIsHackedSucces = bIsValidField;
    bInFocus = false;
    UE_LOG(LogTemp, Display, TEXT("FieldChecked"));
    OnInteractionStop.Broadcast();
}

void ARSTerminal::OnQuitTerminal()
{
    bInFocus = false;
    OnInteractionStop.Broadcast();
}


