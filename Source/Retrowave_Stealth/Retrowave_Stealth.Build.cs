// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Retrowave_Stealth : ModuleRules
{
	public Retrowave_Stealth(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
