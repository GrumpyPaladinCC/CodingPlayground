// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CodingPlayground : ModuleRules
{
	public CodingPlayground(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CodingPlayground",
			"CodingPlayground/Variant_Platforming",
			"CodingPlayground/Variant_Platforming/Animation",
			"CodingPlayground/Variant_Combat",
			"CodingPlayground/Variant_Combat/AI",
			"CodingPlayground/Variant_Combat/Animation",
			"CodingPlayground/Variant_Combat/Gameplay",
			"CodingPlayground/Variant_Combat/Interfaces",
			"CodingPlayground/Variant_Combat/UI",
			"CodingPlayground/Variant_SideScrolling",
			"CodingPlayground/Variant_SideScrolling/AI",
			"CodingPlayground/Variant_SideScrolling/Gameplay",
			"CodingPlayground/Variant_SideScrolling/Interfaces",
			"CodingPlayground/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
