// First shooter developed by Sevenupi

using UnrealBuildTool;

public class Shooter : ModuleRules
{
	public Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"Shooter/Public/Player",
			"Shooter/Public/Componets",
			"Shooter/Public/Development", 
			"Shooter/Public/Weapon", 
			"Shooter/Public/UI",
			"Shooter/Public/Animations",
			"Shooter/Public/Pickups",
			"Shooter/Public/Weapon/Components",
			"Shooter/Public/AI",
			"Shooter/Public/AI/Tasks",
			"Shooter/Public/AI/Services",
			"Shooter/Public/AI/EQS",
			"Shooter/Public/AI/Decorators"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
