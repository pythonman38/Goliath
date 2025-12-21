// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Goliath : ModuleRules
{
	public Goliath(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "GameplayTasks", 
			"GameplayAbilities", "UMG", "AIModule", "AnimGraphRuntime", "MotionWarping"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
