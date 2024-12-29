// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ExMTarget : TargetRules
{
	public ExMTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ExM");
		ExtraModuleNames.Add("EntityConfigEditor");
		ExtraModuleNames.Add("ProceduralDungeon");
	}
}
