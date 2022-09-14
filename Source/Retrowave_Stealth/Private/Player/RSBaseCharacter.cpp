// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RSBaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/RSPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interactable/RSInteractableActor.h"

DEFINE_LOG_CATEGORY_STATIC(RSBaseCharacter_LOG, All, All);

ARSBaseCharacter::ARSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 675.f;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->TargetArmLength = 1000.f;
    SpringArm->SocketOffset = FVector(-500.f, 500.f, 900.f);
    SpringArm->bUsePawnControlRotation = false;
    SpringArm->SetUsingAbsoluteRotation(true);
    SpringArm->bDoCollisionTest = false;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
    FollowCamera->SetupAttachment(SpringArm);

    CameraCollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(FollowCamera);
    CameraCollisionComponent->AddLocalRotation(FRotator(-90.f, 0.f, 0.f));
    CameraCollisionComponent->AddLocalOffset(FVector(0.f, 0.f, 400.f));
    CameraCollisionComponent->InitCapsuleSize(50.f, 600.f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    CameraCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ARSBaseCharacter::SetKilled(bool bNewSet)
{
    bKilled = bNewSet;
    if (!CurrentInteractableObject)
    {
        return;
    }
    CurrentInteractableObject->StopInteractWithObject();
}

void ARSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    check(CameraCollisionComponent);
	
    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARSBaseCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ARSBaseCharacter::OnCameraCollisionEndOverlap);
}

void ARSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ARSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARSBaseCharacter::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARSBaseCharacter::Jump);
    
    DECLARE_DELEGATE_OneParam(FOnCrouchSignature, bool);
    PlayerInputComponent->BindAction<FOnCrouchSignature>("Crouch", IE_Pressed, this, &ARSBaseCharacter::Crouch, true);
    PlayerInputComponent->BindAction<FOnCrouchSignature>("Crouch", IE_Released, this, &ARSBaseCharacter::UnCrouch, true);

    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARSBaseCharacter::InteractWithObject);
}

void ARSBaseCharacter::SetCurrentInteractableObject(ARSInteractableActor* InteractableActor)
{
    FString Test = InteractableActor ? InteractableActor->GetName() : "nullptr";
    UE_LOG(LogTemp, Display, TEXT("actor gained % s "), *Test);
    CurrentInteractableObject = Cast<ARSInteractableActor>(InteractableActor);
}

void ARSBaseCharacter::MoveForward(float Amount)
{
    if (FMath::IsNearlyZero(Amount)) return;

    if (!bIsCrouched)
    {
        MakeNoise(1.0f, this, GetActorLocation());
    }

    AddMovementInput(FVector(1.f, -1.f, 0.f), Amount);
}

void ARSBaseCharacter::MoveRight(float Amount)
{
    if (FMath::IsNearlyZero(Amount)) return;

    if (!bIsCrouched)
    {
        MakeNoise(1.0f, this, GetActorLocation());
    }

    AddMovementInput(FVector(1.f, 1.f, 0.f), Amount);
}

void ARSBaseCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(RSBaseCharacter_LOG, Display, TEXT("Camera touched: %s"), *UKismetSystemLibrary::GetDisplayName(OtherComp));
    //OtherComp->SetVisibility(false);
}

void ARSBaseCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    //OtherComp->SetVisibility(true);
}

void ARSBaseCharacter::InteractWithObject()
{
    FString TestString = CurrentInteractableObject ? CurrentInteractableObject->GetName() : "Now interactable object";
    UE_LOG(LogTemp, Display, TEXT(" % s "), *TestString);
    
    if (!CurrentInteractableObject) return;
    GetMesh()->SetOnlyOwnerSee(true);
    CurrentInteractableObject->InteractWithObject();
}

