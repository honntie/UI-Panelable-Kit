// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PanelTypeLibrary.generated.h"

/**
 * 
 */
UENUM(BlueprintType, meta=(Category="UI Layer Kit | Type"))
enum class EPanelState : uint8
{
	Display,
	Hidden
};