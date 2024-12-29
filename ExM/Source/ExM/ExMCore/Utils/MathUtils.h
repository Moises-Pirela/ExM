#pragma once
#include "Math/UnrealMathUtility.h" // For FMath functions
#include "Exmortalis.h"

inline float NormalizeToRange(const float Value, const float Min, const float Max)
{
    if (FMath::IsNearlyEqual(Min, Max))
    {
        return 0.0f;
    }

    return (Value - Min) / (Max - Min);
}