// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExM : ModuleRules
{
	public ExM(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "AITestSuite" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ProceduralDungeon", "Slate", "SlateCore" });
	}
}
