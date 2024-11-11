public class EditorExtensionsGameEditor : ModuleRules
{
	public EditorExtensionsGameEditor(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"InputCore",
				"SlateCore",
				"GameplayDebugger",
				"GameplayDebuggerExtension",
			}
		);
	}
}