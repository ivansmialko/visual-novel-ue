// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTree.h"

#if WITH_EDITOR
#include "Kismet2/BlueprintEditorUtils.h"
#endif

UDialogueTree::UDialogueTree()
{

}

void UDialogueTree::PostInitProperties()
{
	Super::PostInitProperties();
}

UEdGraph* UDialogueTree::GetGraph()
{
	return DialogueTreeGraph.Get();
}

