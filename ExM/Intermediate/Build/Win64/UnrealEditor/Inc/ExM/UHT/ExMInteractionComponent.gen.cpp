// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ExM/ExMCore/Components/ExMInteractionComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExMInteractionComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
EXM_API UClass* Z_Construct_UClass_UExMInteractionComponent();
EXM_API UClass* Z_Construct_UClass_UExMInteractionComponent_NoRegister();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_ExM();
// End Cross Module References

// Begin Delegate FOnHoverInteractable
struct Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics
{
	struct _Script_ExM_eventOnHoverInteractable_Parms
	{
		FString displayName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_displayName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::NewProp_displayName = { "displayName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ExM_eventOnHoverInteractable_Parms, displayName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::NewProp_displayName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExM, nullptr, "OnHoverInteractable__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::_Script_ExM_eventOnHoverInteractable_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::_Script_ExM_eventOnHoverInteractable_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnHoverInteractable_DelegateWrapper(const FMulticastScriptDelegate& OnHoverInteractable, const FString& displayName)
{
	struct _Script_ExM_eventOnHoverInteractable_Parms
	{
		FString displayName;
	};
	_Script_ExM_eventOnHoverInteractable_Parms Parms;
	Parms.displayName=displayName;
	OnHoverInteractable.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnHoverInteractable

// Begin Delegate FOnClearInteractable
struct Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExM, nullptr, "OnClearInteractable__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnClearInteractable_DelegateWrapper(const FMulticastScriptDelegate& OnClearInteractable)
{
	OnClearInteractable.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FOnClearInteractable

// Begin Class UExMInteractionComponent
void UExMInteractionComponent::StaticRegisterNativesUExMInteractionComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExMInteractionComponent);
UClass* Z_Construct_UClass_UExMInteractionComponent_NoRegister()
{
	return UExMInteractionComponent::StaticClass();
}
struct Z_Construct_UClass_UExMInteractionComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "ExMCore/Components/ExMInteractionComponent.h" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionAction_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_interactionDistance_MetaData[] = {
		{ "Category", "ExMInteractionComponent" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnHoverInteractable_MetaData[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnClearInteractable_MetaData[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_interactionDistance;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnHoverInteractable;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnClearInteractable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExMInteractionComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_InteractionAction = { "InteractionAction", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, InteractionAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionAction_MetaData), NewProp_InteractionAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_interactionDistance = { "interactionDistance", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, interactionDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_interactionDistance_MetaData), NewProp_interactionDistance_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnHoverInteractable = { "OnHoverInteractable", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, OnHoverInteractable), Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnHoverInteractable_MetaData), NewProp_OnHoverInteractable_MetaData) }; // 2424644995
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnClearInteractable = { "OnClearInteractable", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, OnClearInteractable), Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnClearInteractable_MetaData), NewProp_OnClearInteractable_MetaData) }; // 1891410931
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExMInteractionComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_InteractionAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_interactionDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnHoverInteractable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnClearInteractable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMInteractionComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExMInteractionComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ExM,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMInteractionComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExMInteractionComponent_Statics::ClassParams = {
	&UExMInteractionComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UExMInteractionComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UExMInteractionComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExMInteractionComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UExMInteractionComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExMInteractionComponent()
{
	if (!Z_Registration_Info_UClass_UExMInteractionComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExMInteractionComponent.OuterSingleton, Z_Construct_UClass_UExMInteractionComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExMInteractionComponent.OuterSingleton;
}
template<> EXM_API UClass* StaticClass<UExMInteractionComponent>()
{
	return UExMInteractionComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExMInteractionComponent);
UExMInteractionComponent::~UExMInteractionComponent() {}
// End Class UExMInteractionComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExMInteractionComponent, UExMInteractionComponent::StaticClass, TEXT("UExMInteractionComponent"), &Z_Registration_Info_UClass_UExMInteractionComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExMInteractionComponent), 879658256U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_2376708695(TEXT("/Script/ExM"),
	Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
