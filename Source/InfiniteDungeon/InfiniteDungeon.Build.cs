// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InfiniteDungeon : ModuleRules
{
	public InfiniteDungeon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
