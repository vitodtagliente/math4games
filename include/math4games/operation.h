#pragma once

namespace math4games
{
	template <typename T>
	T lerp(const T& a, const T& b, const float t){
		return (1.0f - t) * a + b * t;
	}

	template <typename T>
	T clamp(const T& val, const T& min, const T& max){
		return std::max(min, std::min(val, max));
	}
};