// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ExMCore/Components/ExMInteractionComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
#ifdef EXM_ExMInteractionComponent_generated_h
#error "ExMInteractionComponent.generated.h already included, missing '#pragma once' in ExMInteractionComponent.h"
#endif
#define EXM_ExMInteractionComponent_generated_h

#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_13_DELEGATE \
EXM_API void FOnHoverInteractable_DelegateWrapper(const FMulticastScriptDelegate& OnHoverInteractable, const FString& displayName);


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_14_DELEGATE \
EXM_API void FOnCarry_DelegateWrapper(const FMulticastScriptDelegate& OnCarry, UPrimitiveComponent* carriedComponent);


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_15_DELEGATE \
EXM_API void FOnRelease_DelegateWrapper(const FMulticastScriptDelegate& OnRelease);


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_16_DELEGATE \
EXM_API void FOnThrow_DelegateWrapper(const FMulticastScriptDelegate& OnThrow);


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_17_DELEGATE \
EXM_API void FOnClearInteractable_DelegateWrapper(const FMulticastScriptDelegate& OnClearInteractable);


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_30_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUExMInteractionComponent(); \
	friend struct Z_Construct_UClass_UExMInteractionComponent_Statics; \
public: \
	DECLARE_CLASS(UExMInteractionComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ExM"), NO_API) \
	DECLARE_SERIALIZER(UExMInteractionComponent)


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_30_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UExMInteractionComponent(UExMInteractionComponent&&); \
	UExMInteractionComponent(const UExMInteractionComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UExMInteractionComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UExMInteractionComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UExMInteractionComponent) \
	NO_API virtual ~UExMInteractionComponent();


#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_27_PROLOG
#define FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_30_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_30_INCLASS_NO_PURE_DECLS \
	FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h_30_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> EXM_API UClass* StaticClass<class UExMInteractionComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Components_ExMInteractionComponent_h


#define FOREACH_ENUM_EINTERACTIONTYPE(op) \
	op(INTERACTION_NONE) \
	op(INTERACTION_CARRY) \
	op(INTERACTION_USE) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
