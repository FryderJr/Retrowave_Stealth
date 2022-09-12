// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSLibraryWidget.generated.h"

class UTexture2D;
class UButton;

UCLASS()
class RETROWAVE_STEALTH_API URSLibraryWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* NextKnowlege;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Knowledges")
    TArray<UTexture2D*> FoundKnowledges;
	
private:
    int32 OpendKnowleges{0};
    int32 CurrentKnowlegeIndex{0};
    
    UPROPERTY()
    UTexture2D* CurrentKnowlege;

    void ShowCurrentKnowlege(int32 Index);

    UFUNCTION()
    void OnNextKnowlege();
};
