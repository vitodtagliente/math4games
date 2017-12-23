#pragma once

#include <cmath>
#include <cassert>
#include <initializer_list>
#include <array>

namespace math4games
{
	template<std::size_t n, class T>
	struct vector
	{
		std::array<T, n> data;

		vector() {
			for (auto& element : data)
				element = {};
		}

		vector(const T& value) {
			for (auto& element : data)
				element = value;
		}

		vector(const std::initializer_list<T> args) {
			assert(args.size() < n);
			data = args;
			if (args.size() < n - 1) {
				for (i = args.size(); i < n; i++)
					args[i] = {};
			}
		}

		T& operator[] (const std::size_t i) {
			assert(i >= 0 && i < n);
			return data[i];
		}

		T operator[] (const std::size_t i) const {
			assert(i >= 0 && i < n);
			return data[i];
		}

		T magnitude() const {
			T result = {};
			for (std::size_t i = 0; i < n; ++i)
				result += data[i] * data[i];
			return sqrt(result);
		}

		/*
		vector<n, T> normalize() {
			return (*this * )
		}
		*/
	};

	typedef vector<2, float> vec2;
};