// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogueTree.h"
#include "Toolkits/AssetEditorToolkit.h"

/**
 * 
 */
class DIALOGUESYSTEMEDITOR_API FDialogueTreeEditorToolkit : public FAssetEditorToolkit
{
public:
	void InitEditor(const TArray<UObject*>& InObjects);

	void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	FName GetToolkitFName() const override { return "DialogueTreeEditor"; }
	FText GetBaseToolkitName() const override { return INVTEXT("Dialogue Tree Editor"); }
	FString GetWorldCentricTabPrefix() const override { return "Dialogue Tree"; }
	FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
private:
	TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);

private:
	/** Creates all internal widgets for the tabs to point at */
	void CreateInternalWidgets();

	/** Create new graph editor widget */
	TSharedRef<SGraphEditor> CreateGraphEditorWidget();

	void BindGraphEditorCommands();

private:
	UEdGraph* CreateGraph();

	/** The DialogueTree asset being inspected */
	UDialogueTree* DialogueTree;

	/** New Graph Editor */
	TSharedPtr<class SGraphEditor> DialogueTreeGraphEditor;

	/** Details tab */
	TSharedPtr<class IDetailsView> DetailsView;

	/** Command list for this editor */
	TSharedPtr<FUICommandList> GraphEditorCommands;

	static const FName GraphCanvasTabId;
	static const FName PropertiesTabId;
};
