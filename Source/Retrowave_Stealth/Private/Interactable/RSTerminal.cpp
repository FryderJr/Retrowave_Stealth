// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable/RSTerminal.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraActor.h"
#include "Player/RSBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "RSGameMode.h"
#include "Components/WidgetComponent.h"
#include "MiniGame/MiniGame.h"
#include "RSGameInstance.h"

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

    MiniGameComponent = CreateDefaultSubobject<UWidgetComponent>("MiniGameComonent");
    MiniGameComponent->SetupAttachment(GetRootComponent());
    MiniGameComponent->SetWidgetSpace(EWidgetSpace::World);
}

void ARSTerminal::BeginPlay()
{
	Super::BeginPlay();

    const auto MiniGameWidget = Cast<UMiniGame>(MiniGameComponent->GetUserWidgetObject());
    if (MiniGameWidget)
    {
        MiniGameWidget->OnCheckField.AddUObject(this, &ARSTerminal::OnCheckField);
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

void ARSTerminal::InteractWithObject(ACharacter* Interactor)
{
    if (!Interactor || !bIsActive) return;
    const auto PC = Cast<APlayerController>(Interactor->GetController());

    if (!PC) return;
    PC->SetViewTargetWithBlend(TerminalCamera, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);

    if (!GetWorld() || !GetWorld()->GetAuthGameMode<ARSGameMode>()) return;
    GetWorld()->GetAuthGameMode<ARSGameMode>()->InteractWithObject();

    const auto MiniGameWidget = Cast<UMiniGame>(MiniGameComponent->GetUserWidgetObject());
    if (MiniGameWidget)
    {
        MiniGameWidget->SetKeyboardFocus();
    }
}

void ARSTerminal::StopInteraction(ACharacter* Interactor)
{
    if (!Interactor) return;
    const auto PC = Cast<APlayerController>(Interactor->GetController());

    if (!PC) return;
    PC->SetViewTargetWithBlend(PC->GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
}

void ARSTerminal::OnCheckField(bool bIsValidField)
{
    bIsActive = false;
    bIsHackedSucces = bIsValidField;
    UE_LOG(LogTemp, Display, TEXT("FieldChecked"));

    if (!GetWorld() || !GetWorld()->GetAuthGameMode<ARSGameMode>() || !GetWorld()->GetGameInstance<URSGameInstance>()) return;
    GetWorld()->GetAuthGameMode<ARSGameMode>()->StopInteraction();
    GetWorld()->GetAuthGameMode<ARSGameMode>()->UpdateTerminalData();
}


