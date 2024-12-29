// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ExMCore/Components/ExMHealthComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EXM_ExMHealthComponent_generated_h
#error "ExMHealthComponent.generated.h already included, missing '#pragma once' in ExMHealthComponent.h"
#endif
#define EXM_ExMHealthComponent_generated_h

#define FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_18_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FDamageData_Statics; \
	EXM_API static class UScriptStruct* StaticStruct();


template<> EXM_API UScriptStruct* StaticStruct<struct FDamageData>();

#define FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_30_DELEGATE \
EXM_API void FOnDieSignature_DelegateWrapper(const FMulticastScriptDelegate& OnDieSignature);


#define FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_35_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUExMHealthComponent(); \
	friend struct Z_Construct_UClass_UExMHealthComponent_Statics; \
public: \
	DECLARE_CLASS(UExMHealthComponent, UBaseComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ExM"), NO_API) \
	DECLARE_SERIALIZER(UExMHealthComponent)


#define FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_35_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UExMHealthComponent(UExMHealthComponent&&); \
	UExMHealthComponent(const UExMHealthComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UExMHealthComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UExMHealthComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UExMHealthComponent) \
	NO_API virtual ~UExMHealthComponent();


#define FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_32_PROLOG
#define FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_35_INCLASS_NO_PURE_DECLS \
	FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> EXM_API UClass* StaticClass<class UExMHealthComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Repos_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMHealthComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
