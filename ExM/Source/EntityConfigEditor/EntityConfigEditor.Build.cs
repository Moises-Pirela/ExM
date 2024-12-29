using UnrealBuildTool;

public class EntityConfigEditor : ModuleRules
{
	public EntityConfigEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "EntityConfigEditor", "ExM" });
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UnrealEd", "PropertyEditor", "ExM"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}