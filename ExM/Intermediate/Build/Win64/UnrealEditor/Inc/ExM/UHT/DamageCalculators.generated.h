// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ExMCore/Utils/DamageCalculators.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef EXM_DamageCalculators_generated_h
#error "DamageCalculators.generated.h already included, missing '#pragma once' in DamageCalculators.h"
#endif
#define EXM_DamageCalculators_generated_h

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_NecrotekLabs_ExMORTALIS_ExM_Source_ExM_ExMCore_Utils_DamageCalculators_h


#define FOREACH_ENUM_EDAMAGETYPES(op) \
	op(DAMAGE_TYPE_KINETIC) \
	op(DAMAGE_TYPE_BLUNT) \
	op(DAMAGE_TYPE_SLASH) \
	op(DAMAGE_TYPE_NECROTIC) \
	op(DAMAGE_TYPE_FALL) 

enum EDamageTypes : int;
template<> EXM_API UEnum* StaticEnum<EDamageTypes>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
