﻿// Copyright (c) 2022 Jonas Reich

#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "OUUBlueprintClassFlags.generated.h"

/**
 * These flags are copies of EClassFlags exposed for Blueprint use.
 * Do not use as bitmasks directly - these enum cases must be converted using the blueprint functions from
 * UOUUBlueprintClassFlagsLibrary.
 *
 * Please check that source enum for more detailed documentation on general flags usage and individual flags purpose.
 */
UENUM(BlueprintType)
enum class EOUUBlueprintClassFlags : uint8
{
	/** No Flags */
	None,
	/** Class is abstract and can't be instantiated directly. */
	Abstract,
	/** Save object configuration only to Default INIs, never to local INIs. Must be combined with Config */
	DefaultConfig,
	/** Load object configuration at construction time. */
	Config,
	/** This object type can't be saved; null it out at save time. */
	Transient,
	/** Successfully parsed. */
	Parsed,

	MatchedSerializers,
	/** Indicates that the config settings for this class will be saved to Project/User*.ini (similar to
	   GlobalUserConfig) */
	ProjectUserConfig,
	/** Class is a native class - native interfaces will have Native set, but not RF_MarkAsNative */
	Native,
	/** Don't export to C++ header. */
	NoExport,
	/** Do not allow users to create in the editor. */
	NotPlaceable,
	/** Handle object configuration on a per-object basis, rather than per-class. */
	PerObjectConfig,

	/** Whether SetUpRuntimeReplicationData still needs to be called for this class */
	ReplicationDataIsSetUp,

	/** Class can be constructed from editinline New button. */
	EditInlineNew,
	/** Display properties in the editor without using categories. */
	CollapseCategories,
	/** Class is an interface **/
	Interface,
	/**  Do not export a constructor for this class, assuming it is in the cpptext **/
	CustomConstructor,
	/** all properties and functions in this class are const and should be exported as const */
	Const,

	/** Class flag indicating the class is having its layout changed, and therefore is not ready for a CDO to be created
	 */
	LayoutChanging,

	/** Indicates that the class was created from blueprint source material */
	CompiledFromBlueprint,

	/** Indicates that only the bare minimum bits of this class should be DLL exported/imported */
	MinimalAPI,

	/** Indicates this class must be DLL exported/imported (along with all of it's members) */
	RequiredAPI,

	/** Indicates that references to this class default to instanced. Used to be subclasses of UComponent, but now can
	   be any UObject */
	DefaultToInstanced,

	/** Indicates that the parent token stream has been merged with ours. */
	TokenStreamAssembled,
	/** Class has component properties. */
	HasInstancedReference,
	/** Don't show this class in the editor class browser or edit inline new menus. */
	Hidden,
	/** Don't save objects of this class when serializing */
	Deprecated,
	/** Class not shown in editor drop down for class selection */
	HideDropDown,
	/** Class settings are saved to <AppData>/..../Blah.ini (as opposed to DefaultConfig) */
	GlobalUserConfig,
	/** Class was declared directly in C++ and has no boilerplate generated by UnrealHeaderTool */
	Intrinsic,
	/** Class has already been constructed (maybe in a previous DLL version before hot-reload). */
	Constructed,
	/** Indicates that object configuration will not check against ini base/defaults when serialized */
	ConfigDoNotCheckDefaults,
	/** Class has been consigned to oblivion as part of a blueprint recompile, and a newer version currently exists. */
	NewerVersionExists,
	/** Flags to inherit from base class */
	Inherit,
	/** These flags will be cleared by the compiler when the class is parsed during script compilation */
	RecompilerClear,
	/** These flags will be cleared by the compiler when the class is parsed during script compilation */
	ShouldNeverBeLoaded,

	/** These flags will be inherited from the base class only for non-intrinsic classes */
	ScriptInherit,

	/** This is used as a mask for the flags put into generated code for "compiled in" classes. */
	SaveInCompiledInClasses,

	AllFlags
};

UCLASS()
class UOUUBlueprintClassFlagsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Open Unreal Utilities|Class Flags")
	static int64 CreateClassFlagsMask(TSet<EOUUBlueprintClassFlags> Flags);

	UFUNCTION(BlueprintPure, Category = "Open Unreal Utilities|Class Flags")
	static TSet<EOUUBlueprintClassFlags> BreakClassFlagsMask(int64 Flags);

	UFUNCTION(BlueprintPure, Category = "Open Unreal Utilities|Class Flags")
	static TSet<EOUUBlueprintClassFlags> GetClassFlagsSet(const UClass* Class);

	UFUNCTION(BlueprintPure, Category = "Open Unreal Utilities|Class Flags")
	static int64 GetClassFlagsMask(const UClass* Class);

	UFUNCTION(BlueprintPure, Category = "Open Unreal Utilities|Class Flags")
	static bool ClassHasAnyFlags(const UClass* Class, TSet<EOUUBlueprintClassFlags> Flags);

	UFUNCTION(BlueprintPure, Category = "Open Unreal Utilities|Class Flags")
	static bool ClassHasAllFlags(const UClass* Class, TSet<EOUUBlueprintClassFlags> Flags);
};
