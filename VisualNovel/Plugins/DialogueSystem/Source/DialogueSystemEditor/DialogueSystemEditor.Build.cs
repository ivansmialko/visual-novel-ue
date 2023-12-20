// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
	public DialogueSystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				System.IO.Path.Combine(GetModuleDirectory("GraphEditor"), "Private"),
            }
            );
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "ApplicationCore",
                "AudioMixer",
                "SignalProcessing",
                "InputCore",
                "Engine",
                "EditorFramework",
                "UnrealEd",
                "Slate",
                "SlateCore",

                "RenderCore",
                "LevelEditor",
                "Landscape",
                "PropertyEditor",
                "DetailCustomizations",
                "ClassViewer",
                "GraphEditor",
                "ContentBrowser",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "DialogueSystem",
				"AudioMixer",
                "EditorSubsystem",
                "GameProjectGeneration",
                "ToolMenus",
                "UMG",
                "DeveloperSettings",
                "UMGEditor",
                "AudioExtensions",
                "AudioLinkEngine"
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
