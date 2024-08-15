// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ExM/ExMCore/Components/ExMResistancesComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeExMResistancesComponent() {}

// Begin Cross Module References
EXM_API UClass* Z_Construct_UClass_UBaseComponent();
EXM_API UClass* Z_Construct_UClass_UExMResistancesComponent();
EXM_API UClass* Z_Construct_UClass_UExMResistancesComponent_NoRegister();
EXM_API UEnum* Z_Construct_UEnum_ExM_EDamageTypes();
UPackage* Z_Construct_UPackage__Script_ExM();
// End Cross Module References

// Begin Class UExMResistancesComponent
void UExMResistancesComponent::StaticRegisterNativesUExMResistancesComponent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UExMResistancesComponent);
UClass* Z_Construct_UClass_UExMResistancesComponent_NoRegister()
{
	return UExMResistancesComponent::StaticClass();
}
struct Z_Construct_UClass_UExMResistancesComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "ExMortalis" },
		{ "IncludePath", "ExMCore/Components/ExMResistancesComponent.h" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMResistancesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Resistances_MetaData[] = {
		{ "Category", "ExMResistancesComponent" },
		{ "ModuleRelativePath", "ExMCore/Components/ExMResistancesComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Resistances_ValueProp;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Resistances_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Resistances;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UExMResistancesComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UExMResistancesComponent_Statics::NewProp_Resistances_ValueProp = { "Resistances", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UExMResistancesComponent_Statics::NewProp_Resistances_Key_KeyProp = { "Resistances_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UEnum_ExM_EDamageTypes, METADATA_PARAMS(0, nullptr) }; // 3325920591
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UExMResistancesComponent_Statics::NewProp_Resistances = { "Resistances", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UExMResistancesComponent, Resistances), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Resistances_MetaData), NewProp_Resistances_MetaData) }; // 3325920591
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UExMResistancesComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMResistancesComponent_Statics::NewProp_Resistances_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMResistancesComponent_Statics::NewProp_Resistances_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UExMResistancesComponent_Statics::NewProp_Resistances,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMResistancesComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UExMResistancesComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBaseComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ExM,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UExMResistancesComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UExMResistancesComponent_Statics::ClassParams = {
	&UExMResistancesComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UExMResistancesComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UExMResistancesComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UExMResistancesComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UExMResistancesComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UExMResistancesComponent()
{
	if (!Z_Registration_Info_UClass_UExMResistancesComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UExMResistancesComponent.OuterSingleton, Z_Construct_UClass_UExMResistancesComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UExMResistancesComponent.OuterSingleton;
}
template<> EXM_API UClass* StaticClass<UExMResistancesComponent>()
{
	return UExMResistancesComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UExMResistancesComponent);
UExMResistancesComponent::~UExMResistancesComponent() {}
// End Class UExMResistancesComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMResistancesComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UExMResistancesComponent, UExMResistancesComponent::StaticClass, TEXT("UExMResistancesComponent"), &Z_Registration_Info_UClass_UExMResistancesComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UExMResistancesComponent), 328164368U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMResistancesComponent_h_3602638079(TEXT("/Script/ExM"),
	Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMResistancesComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMResistancesComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
