using UnrealBuildTool;

public class SOAPClientTarget : TargetRules
{
	public SOAPClientTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Client;
		ExtraModuleNames.Add("SOAP");
	}
}
