// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EquipAuto : ModuleRules
{
	public EquipAuto(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp17;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "UMG", "Slate", "SlateCore" });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"EquipAuto",
			"EquipAuto/UI",
			"EquipAuto/Equipment",
			"EquipAuto/Core",
			"EquipAuto/Algorithm",
		});
	}
}
