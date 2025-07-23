// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Koyan_Casino_ClimbEditorTarget : TargetRules
{
	public Koyan_Casino_ClimbEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "Koyan_Casino_Climb" } );
	}
}
