// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RSBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class UCapsuleComponent;

class ARSInteractableActor;

class ACameraActor;

UCLASS()
class RETROWAVE_STEALTH_API ARSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARSBaseCharacter();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    UCapsuleComponent* CameraCollisionComponent;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void SetCurrentInteractableObject(ARSInteractableActor* InteractableActor);

    UFUNCTION(BlueprintCallable)
    bool GetReadyToTalk() const { return bIsReadyToTalk; };
    UFUNCTION(BlueprintCallable)
    void SetReadyToTalk(bool Enabled) { bIsReadyToTalk = Enabled; };

private:
    UPROPERTY(SaveGame)
    bool bIsReadyToTalk{true};

    UPROPERTY()
    ARSInteractableActor* CurrentInteractableObject{nullptr};

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void InteractWithObject();
};
