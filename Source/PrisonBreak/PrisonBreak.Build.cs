// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PrisonBreak : ModuleRules
{
	public PrisonBreak(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule", "NavigationSystem", "UMG" });
	}
}
