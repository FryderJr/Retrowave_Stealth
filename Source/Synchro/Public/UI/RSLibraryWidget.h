// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RSTypes.h"
#include "RSLibraryWidget.generated.h"

class UTexture2D;
class UButton;

UCLASS()
class SYNCHRO_API URSLibraryWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable)
    FKnowlegeData GetCurrentKnowlege() const { return CurrentKnowlege; };

    UFUNCTION(BlueprintCallable)
    int32 GetCurrentKnowlegeIndex() const { return CurrentKnowlegeIndex; };

    UFUNCTION(BlueprintNativeEvent)
    void OnShowCurrentKnowlege_BP(int32 Index);

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* NextKnowlegeButton;

    UPROPERTY(meta = (BindWidget))
    UButton* PrevKnowlegeButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Knowledges")
    TArray<FKnowlegeData> FoundKnowledges;

private:
    int32 OpenedKnowleges{0};
    int32 CurrentKnowlegeIndex{0};
    
    UPROPERTY()
    FKnowlegeData CurrentKnowlege;

    UFUNCTION()
    void OnNextKnowlege();

    UFUNCTION()
    void OnPrevKnowlege();

    void ShowCurrentKnowlege(int32 Index);
};
