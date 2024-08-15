#pragma once

constexpr int MAX_ENTITIES = 100;
constexpr float UE_UNITS_TO_METERS = 100;

inline float EaseInOutSine(float x)
{
	return -(FMath::Cos(PI * x) - 1) / 2;
}

