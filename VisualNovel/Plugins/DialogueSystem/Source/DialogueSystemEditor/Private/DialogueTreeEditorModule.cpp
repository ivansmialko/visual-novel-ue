// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueTreeEditorModule.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemEditorModule"

void FDialogueSystemEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	DialogueTreeAssetTypeActions = MakeShared<FDialogueTreeAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(DialogueTreeAssetTypeActions.ToSharedRef());
}

void FDialogueSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
		return;

	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(DialogueTreeAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)