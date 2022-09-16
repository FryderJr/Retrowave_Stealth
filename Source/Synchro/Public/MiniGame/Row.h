// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Row.generated.h"

/**
 * 
 */
UCLASS()
class SYNCHRO_API URow : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* RowCanvas;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* Rows;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UColumn* Column1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UColumn* Column2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UColumn* Column3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UColumn* Column4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UColumn* Column5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UColumn* Column6;*/
};
