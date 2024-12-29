#pragma once

constexpr int MAX_ENTITY_COUNT = 100;
constexpr int MAX_ATTRIBUTE_VALUE = 30;
constexpr float UE_UNITS_TO_METERS = 100;

inline float EaseInOutSine(float x)
{
	return -(FMath::Cos(PI * x) - 1) / 2;
}



