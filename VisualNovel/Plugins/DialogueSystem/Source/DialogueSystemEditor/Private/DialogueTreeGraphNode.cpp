// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTreeGraphNode.h"

FText UDialogueTreeNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return INVTEXT("Dialogue Node");
}
