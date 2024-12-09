// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GamesGroupProject : ModuleRules
{
	public GamesGroupProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore",
			"UMG", "EnhancedInput", "AIModule", "GameplayTasks", "NavigationSystem"
		});
	}
}