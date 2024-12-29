// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ExM/ExMCore/Components/ExMHealthComponent.h"
#include "ExM/ExMCore/Buffables.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExMHealthComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
EXM_API UClass* Z_Construct_UClass_UBaseComponent();
EXM_API UClass* Z_Construct_UClass_UExMHealthComponent();
EXM_API UClass* Z_Construct_UClass_UExMHealthComponent_NoRegister();
EXM_API UEnum* Z_Construct_UEnum_ExM_EDamageTypes();
EXM_API UFunction* Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature();
EXM_API UScriptStruct* Z_Construct_UScriptStruct_FBuffableFloat();
EXM_API UScriptStruct* Z_Construct_UScriptStruct_FDamageData();
UPackage* Z_Construct_UPackage__Script_ExM();
// End Cross Module References

// Begin ScriptStruct FDamageData
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_DamageData;
class UScriptStruct* FDamageData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_DamageData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_DamageData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FDamageData, (UObject*)Z_Construct_UPackage__Script_ExM(), TEXT("DamageData"));
	}
	return Z_Registration_Info_UScriptStruct_DamageData.OuterSingleton;
}
template<> EXM_API UScriptStruct* StaticStruct<FDamageData>()
{
	return FDamageData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FDamageData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_baseDamage_MetaData[] = {
		{ "Category", "DamageData" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_pDamageDealer_MetaData[] = {
		{ "Category", "DamageData" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_damageType_MetaData[] = {
		{ "Category", "DamageData" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_baseDamage;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_pDamageDealer;
	static const UECodeGen_Private::FBytePropertyParams NewProp_damageType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FDamageData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FDamageData_Statics::NewProp_baseDamage = { "baseDamage", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDamageData, baseDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_baseDamage_MetaData), NewProp_baseDamage_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FDamageData_Statics::NewProp_pDamageDealer = { "pDamageDealer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDamageData, pDamageDealer), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_pDamageDealer_MetaData), NewProp_pDamageDealer_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FDamageData_Statics::NewProp_damageType = { "damageType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FDamageData, damageType), Z_Construct_UEnum_ExM_EDamageTypes, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_damageType_MetaData), NewProp_damageType_MetaData) }; // 3325920591
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FDamageData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDamageData_Statics::NewProp_baseDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDamageData_Statics::NewProp_pDamageDealer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FDamageData_Statics::NewProp_damageType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDamageData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FDamageData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_ExM,
	nullptr,
	&NewStructOps,
	"DamageData",
	Z_Construct_UScriptStruct_FDamageData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDamageData_Statics::PropPointers),
	sizeof(FDamageData),
	alignof(FDamageData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FDamageData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FDamageData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FDamageData()
{
	if (!Z_Registration_Info_UScriptStruct_DamageData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_DamageData.InnerSingleton, Z_Construct_UScriptStruct_FDamageData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_DamageData.InnerSingleton;
}
// End ScriptStruct FDamageData

// Begin Delegate FOnDieSignature
struct Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_ExM, nullptr, "OnDieSignature__DelegateSignature", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnDieSignature_DelegateWrapper(const FMulticastScriptDelegate& OnDieSignature)
{
	OnDieSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// End Delegate FOnDieSignature

// Begin Class UExMHealthComponent
void UExMHealthComponent::StaticRegisterNativesUExMHealthComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExMHealthComponent);
UClass* Z_Construct_UClass_UExMHealthComponent_NoRegister()
{
	return UExMHealthComponent::StaticClass();
}
struct Z_Construct_UClass_UExMHealthComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "ExMORTALIS" },
		{ "IncludePath", "ExMCore/Components/ExMHealthComponent.h" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_maxHealth_MetaData[] = {
		{ "Category", "ExMHealthComponent" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDie_MetaData[] = {
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_currentHealth_MetaData[] = {
		{ "Category", "ExMHealthComponent" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMHealthComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_maxHealth;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDie;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_currentHealth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExMHealthComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UExMHealthComponent_Statics::NewProp_maxHealth = { "maxHealth", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMHealthComponent, maxHealth), Z_Construct_UScriptStruct_FBuffableFloat, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_maxHealth_MetaData), NewProp_maxHealth_MetaData) }; // 2828805209
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UExMHealthComponent_Statics::NewProp_OnDie = { "OnDie", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMHealthComponent, OnDie), Z_Construct_UDelegateFunction_ExM_OnDieSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDie_MetaData), NewProp_OnDie_MetaData) }; // 3904414349
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UExMHealthComponent_Statics::NewProp_currentHealth = { "currentHealth", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMHealthComponent, currentHealth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_currentHealth_MetaData), NewProp_currentHealth_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExMHealthComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMHealthComponent_Statics::NewProp_maxHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMHealthComponent_Statics::NewProp_OnDie,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMHealthComponent_Statics::NewProp_currentHealth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMHealthComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExMHealthComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBaseComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ExM,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMHealthComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExMHealthComponent_Statics::ClassParams = {
	&UExMHealthComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UExMHealthComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UExMHealthComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExMHealthComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UExMHealthComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExMHealthComponent()
{
	if (!Z_Registration_Info_UClass_UExMHealthComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExMHealthComponent.OuterSingleton, Z_Construct_UClass_UExMHealthComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExMHealthComponent.OuterSingleton;
}
template<> EXM_API UClass* StaticClass<UExMHealthComponent>()
{
	return UExMHealthComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExMHealthComponent);
UExMHealthComponent::~UExMHealthComponent() {}
// End Class UExMHealthComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FDamageData::StaticStruct, Z_Construct_UScriptStruct_FDamageData_Statics::NewStructOps, TEXT("DamageData"), &Z_Registration_Info_UScriptStruct_DamageData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FDamageData), 2290297756U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExMHealthComponent, UExMHealthComponent::StaticClass, TEXT("UExMHealthComponent"), &Z_Registration_Info_UClass_UExMHealthComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExMHealthComponent), 2409253982U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_2526057503(TEXT("/Script/ExM"),
	Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
