using UnrealBuildTool;

public class SOAPEditorTarget : TargetRules
{
	public SOAPEditorTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		Type = TargetType.Editor;
		ExtraModuleNames.Add("SOAP");
	}
}
