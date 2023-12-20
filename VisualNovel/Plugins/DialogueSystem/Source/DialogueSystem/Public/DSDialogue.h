// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DSDialogue.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UDSDialogue : public UObject
{
	GENERATED_BODY()

public:
	//TArray<class DSDialodueNode> DialogueNodes;
	uint32 DialogueId;
};
