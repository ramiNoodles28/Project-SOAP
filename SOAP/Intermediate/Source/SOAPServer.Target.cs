using UnrealBuildTool;

public class SOAPServerTarget : TargetRules
{
	public SOAPServerTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Server;
		ExtraModuleNames.Add("SOAP");
	}
}
