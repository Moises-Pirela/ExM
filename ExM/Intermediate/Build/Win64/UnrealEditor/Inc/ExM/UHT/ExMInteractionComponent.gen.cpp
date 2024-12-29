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
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
EXM_API UClass* Z_Construct_UClass_UBaseComponent();
EXM_API UClass* Z_Construct_UClass_UExMInteractionComponent();
EXM_API UClass* Z_Construct_UClass_UExMInteractionComponent_NoRegister();
EXM_API UEnum* Z_Construct_UEnum_ExM_EInteractionType();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnClearInteractable__DelegateSignature();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnHoverInteractable__DelegateSignature();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature();
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

// Begin Delegate FOnCarry
struct Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics
{
	struct _Script_ExM_eventOnCarry_Parms
	{
		UPrimitiveComponent* carriedComponent;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_carriedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_carriedComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::NewProp_carriedComponent = { "carriedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ExM_eventOnCarry_Parms, carriedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_carriedComponent_MetaData), NewProp_carriedComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::NewProp_carriedComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExM, nullptr, "OnCarry__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::_Script_ExM_eventOnCarry_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::_Script_ExM_eventOnCarry_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnCarry_DelegateWrapper(const FMulticastScriptDelegate& OnCarry, UPrimitiveComponent* carriedComponent)
{
	struct _Script_ExM_eventOnCarry_Parms
	{
		UPrimitiveComponent* carriedComponent;
	};
	_Script_ExM_eventOnCarry_Parms Parms;
	Parms.carriedComponent=carriedComponent;
	OnCarry.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FOnCarry

// Begin Delegate FOnRelease
struct Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExM, nullptr, "OnRelease__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnRelease_DelegateWrapper(const FMulticastScriptDelegate& OnRelease)
{
	OnRelease.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FOnRelease

// Begin Delegate FOnThrow
struct Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExM, nullptr, "OnThrow__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnThrow_DelegateWrapper(const FMulticastScriptDelegate& OnThrow)
{
	OnThrow.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FOnThrow

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

// Begin Enum EInteractionType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EInteractionType;
static UEnum* EInteractionType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EInteractionType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EInteractionType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ExM_EInteractionType, (UObject*)Z_Construct_UPackage__Script_ExM(), TEXT("EInteractionType"));
	}
	return Z_Registration_Info_UEnum_EInteractionType.OuterSingleton;
}
template<> EXM_API UEnum* StaticEnum<EInteractionType>()
{
	return EInteractionType_StaticEnum();
}
struct Z_Construct_UEnum_ExM_EInteractionType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "INTERACTION_CARRY.Name", "INTERACTION_CARRY" },
		{ "INTERACTION_NONE.Name", "INTERACTION_NONE" },
		{ "INTERACTION_USE.Name", "INTERACTION_USE" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "INTERACTION_NONE", (int64)INTERACTION_NONE },
		{ "INTERACTION_CARRY", (int64)INTERACTION_CARRY },
		{ "INTERACTION_USE", (int64)INTERACTION_USE },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ExM_EInteractionType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ExM,
	nullptr,
	"EInteractionType",
	"EInteractionType",
	Z_Construct_UEnum_ExM_EInteractionType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ExM_EInteractionType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::Regular,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ExM_EInteractionType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ExM_EInteractionType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ExM_EInteractionType()
{
	if (!Z_Registration_Info_UEnum_EInteractionType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EInteractionType.InnerSingleton, Z_Construct_UEnum_ExM_EInteractionType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EInteractionType.InnerSingleton;
}
// End Enum EInteractionType

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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnCarry_MetaData[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnRelease_MetaData[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnThrow_MetaData[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_currentInteractionType_MetaData[] = {
		{ "Category", "ExMInteractionComponent" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_grabbedComponent_MetaData[] = {
		{ "Category", "ExMInteractionComponent" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMInteractionComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_interactionDistance;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnHoverInteractable;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnClearInteractable;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnCarry;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnRelease;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnThrow;
	static const UECodeGen_Private::FBytePropertyParams NewProp_currentInteractionType;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_grabbedComponent;
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
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnCarry = { "OnCarry", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, OnCarry), Z_Construct_UDelegateFunction_ExM_OnCarry__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnCarry_MetaData), NewProp_OnCarry_MetaData) }; // 328697000
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnRelease = { "OnRelease", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, OnRelease), Z_Construct_UDelegateFunction_ExM_OnRelease__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnRelease_MetaData), NewProp_OnRelease_MetaData) }; // 908413431
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnThrow = { "OnThrow", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, OnThrow), Z_Construct_UDelegateFunction_ExM_OnThrow__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnThrow_MetaData), NewProp_OnThrow_MetaData) }; // 4213444293
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_currentInteractionType = { "currentInteractionType", nullptr, (EPropertyFlags)0x0010000000020005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, currentInteractionType), Z_Construct_UEnum_ExM_EInteractionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_currentInteractionType_MetaData), NewProp_currentInteractionType_MetaData) }; // 2612140709
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_grabbedComponent = { "grabbedComponent", nullptr, (EPropertyFlags)0x00100000000a000d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMInteractionComponent, grabbedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_grabbedComponent_MetaData), NewProp_grabbedComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExMInteractionComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_InteractionAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_interactionDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnHoverInteractable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnClearInteractable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnCarry,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnRelease,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_OnThrow,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_currentInteractionType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMInteractionComponent_Statics::NewProp_grabbedComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMInteractionComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExMInteractionComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBaseComponent,
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
struct Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EInteractionType_StaticEnum, TEXT("EInteractionType"), &Z_Registration_Info_UEnum_EInteractionType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2612140709U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExMInteractionComponent, UExMInteractionComponent::StaticClass, TEXT("UExMInteractionComponent"), &Z_Registration_Info_UClass_UExMInteractionComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExMInteractionComponent), 4005326680U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_4192523471(TEXT("/Script/ExM"),
	Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
