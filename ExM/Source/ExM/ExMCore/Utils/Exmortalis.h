#pragma once

constexpr int MAX_ENTITIES = 100;
constexpr float UE_UNITS_TO_METERS = 100;

inline float EaseInOutSine(float x)
{
	return -(FMath::Cos(PI * x) - 1) / 2;
}

inline float rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;
	i  = 0x5f3759df - ( i >> 1 );
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );

	return y;
}

