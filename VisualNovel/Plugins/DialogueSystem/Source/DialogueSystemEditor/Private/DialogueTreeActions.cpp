// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueTreeActions.h"
#include "DialogueTree.h"
#include "DialogueTreeEditorToolkit.h"

UClass* FDialogueTreeAssetTypeActions::GetSupportedClass() const
{
	return UDialogueTree::StaticClass();
}

FText FDialogueTreeAssetTypeActions::GetName() const
{
	return INVTEXT("Dialogue Tree");
}

FColor FDialogueTreeAssetTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

uint32 FDialogueTreeAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FDialogueTreeAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	MakeShared<FDialogueTreeEditorToolkit>()->InitEditor(InObjects);
}
