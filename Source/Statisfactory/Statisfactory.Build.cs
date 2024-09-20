using UnrealBuildTool;

// ReSharper disable RedundantExplicitArrayCreation
// ReSharper disable UseCollectionExpression

public class Statisfactory : ModuleRules {
    public Statisfactory(ReadOnlyTargetRules target) : base(target) {
        this.PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        this.PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject",
            "Engine",
            "DeveloperSettings",
            "PhysicsCore",
            "InputCore",
            //"OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull",
            //"SignificanceManager",
            "GeometryCollectionEngine",
            //"ChaosVehiclesCore", "ChaosVehicles", "ChaosSolverEngine",
            "AnimGraphRuntime",
            //"AkAudio",
            "AssetRegistry",
            "NavigationSystem",
            //"ReplicationGraph",
            "AIModule",
            "GameplayTasks",
            "SlateCore", "Slate", "UMG",
            //"InstancedSplines",
            "RenderCore",
            "CinematicCamera",
            "Foliage",
            //"Niagara",
            //"EnhancedInput",
            //"GameplayCameras",
            //"TemplateSequence",
            "NetCore",
            "GameplayTags",
            "Json", "JsonUtilities"
        });

        // FactoryGame plugins
        this.PublicDependencyModuleNames.AddRange(new string[] {
            //"AbstractInstance",
            //"InstancedSplinesComponent",
            //"SignificanceISPC"
        });

        // Header stubs
        this.PublicDependencyModuleNames.AddRange(new string[] {
            "DummyHeaders",
        });

        if (target.Type == TargetRules.TargetType.Editor) {
            this.PublicDependencyModuleNames.AddRange(new string[] { /*"OnlineBlueprintSupport",*/ "AnimGraph"});
        }

        this.PublicDependencyModuleNames.AddRange(new string[] {"FactoryGame", "FactoryDedicatedServer"});

        this.PublicIncludePaths.AddRange(new string[] {
            // ... add public include paths required here ...
        });

        this.PrivateIncludePaths.AddRange(new string[] {
            // ... add private include paths required here ...
        });

        this.PublicDependencyModuleNames.AddRange(new string[] {
            // ... add public dependencies that you statically link with here ...
        });

        this.PrivateDependencyModuleNames.AddRange(new string[] {
            // ... add private dependencies that you statically link with here ...
        });

        this.DynamicallyLoadedModuleNames.AddRange(new string[] {
            // ... add any modules that your module loads dynamically here ...
        });
    }
}
