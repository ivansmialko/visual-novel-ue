// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DSDialogueNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UDSDialogueNode : public UObject
{
	GENERATED_BODY()

public:
	int32 NodeId {0};
	int32 NextNodeId{0};
	FText NodeText { INVTEXT("Empty") };
	//Reply list
	UTexture2D* CharacterImage;
	UTexture2D* BackgroundImage;
};
