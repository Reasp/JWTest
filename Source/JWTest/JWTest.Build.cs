// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JWTest : ModuleRules
{
	public JWTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
                "JWTest"
            }
        );

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
