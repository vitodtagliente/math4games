#pragma once

/*
	common math oprations
	Vito Domenico Tagliente
	math library for games
*/

#include <cmath>

namespace math4games
{
	const float pi = 3.14159265358979f;

	float deg2rad(const float theta) {
		return 360 * theta / pi;
	}

	float rad2deg(const float theta) {
		return theta * pi / 360;
	}

	template <typename T>
	T lerp(const T& a, const T& b, const float t) {
		return (1.0f - t) * a + b * t;
	}

	template <typename T>
	T clamp(const T& val, const T& min, const T& max) {
		return std::max(min, std::min(val, max));
	}
};