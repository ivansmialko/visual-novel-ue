// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueTreeGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueTreeNode : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

};
