// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Synchro : ModuleRules
{
	public Synchro(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "SLATECORE" });
        
        PublicIncludePaths.AddRange(new string[]
        {
            "Synchro/Public/Menu",
            "Synchro/Public/Menu/UI",
            "Synchro/Public/Player",
            "Synchro/Public/UI"
        });
	}
}
