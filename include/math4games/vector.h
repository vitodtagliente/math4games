#pragma once

/*
vector implementation
credits: Vito Domenico Tagliente
*/

#include <cmath>
#include <cassert>
#include <initializer_list>
#include <array>

namespace math4games
{
	template<std::size_t n, typename T>
	struct vec
	{
		std::array<T, n> data;

		vec() {
			data.fill(T{});
		}

		vec(const T& value) {
			data.fill(value);
		}

		vec(const std::initializer_list<T> args) {
			assert(args.size() <= n);
			int i = 0;
			for (auto begin = args.begin(); begin != args.end(); ++begin) {
				data.at(i) = *begin;
				i++;
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

		T distance(const vec<n, T>& other) const {
			return (*this - other).magnitude();
		}

		static T distance(const vec<n, T>& v, const vec<n, T>& w) {
			return (v - w).magnitude();
		}

		T dot(const vec<n, T>& other) const {
			return (*this)*other;
		}

		static T dot(const vec<n, T>& v, const vec<n, T>& w) {
			return v*w;
		}

		vec<n, T> normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		vec<n, T> project(const vec<n, T>& v) {
			return v* ((*this*v) / (v*v));
		}
		
		vec<n, T> reject(const vec<n, T>& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}
		
		/* Operators overloading */

		vec<n, T>& operator= (const vec<n, T>& other) {
			/* check for self-assignment */
			if (this == &other)
				return *this;

			/* copy */
			data = other.data;
			return *this;
		}

		bool operator== (const vec<n, T>& other) const {
			return (*this).data == other.data;
		}

		bool operator!= (const vec<n, T>& other) const {
			return !(*this == other);
		}

		vec<n, T>& operator+= (const vec<n, T>& other) {
			for (std::size_t i = 0; i < n; i++)
				data[i] += other[i];
			return *this;
		}

		vec<n, T>& operator-= (const vec<n, T>& other) {
			for (std::size_t i = 0; i < n; i++)
				data[i] -= other[i];
			return *this;
		}

		vec<n, T>& operator*= (const T s) {
			for (std::size_t i = 0; i < n; i++)
				data[i] *= s;
			return *this;
		}

		vec<n, T>& operator/= (const T s) {
			T f = 1.0f / s;
			for (std::size_t i = 0; i < n; i++)
				data[i] *= f;
			return *this;
		}

		vec<n, T> operator- () const {
			vec<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = -data[i];
			return v;
		}

		vec<n, T> operator+ (const vec<n, T>& w) const {
			vec<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] + w[i];
			return v;
		}

		vec<n, T> operator- (const vec<n, T>& w) const {
			vec<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] - w[i];
			return v;
		}

		vec<n, T> operator* (const T s) const {
			vec<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] * s;
			return v;
		}

		vec<n, T> operator/ (const T s) const {
			T f = 1.0f / s;
			vec<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] * f;
			return v;
		}

		/* dot product */
		T operator*(const vec<n, T>& v) const {
			T dot{};
			for (std::size_t i = 0; i < n; i++)
				dot += data[i] * v[i];
			return dot;
		}
	};

	template<std::size_t n, class T>
	inline vec<n, T> operator* (const T s, const vec<n, T>& v) {
		vec<n, T> w;
		for (std::size_t i = 0; i < n; i++)
			w[i] = v[i] * s;
		return w;
	}

	template<typename T>
	struct tvec2 : public vec<2, T>
	{
		float& x = data[0];
		float& y = data[1];

		tvec2() : vec<2, T>() {}
		tvec2(T _x, T _y) {
			data[0] = _x;
			data[1] = _y;
		}
		tvec2(const vec<2, T>& v) {
			data = v.data;
		}
		tvec2(const T& value) : vec<2, T>(value) {}
		tvec2(const std::initializer_list<T> args) : vec<2, T>(args) {}

		tvec2<T>& operator= (const vec<2, T>& v) {
			data = v.data;
			return *this;
		}

		static const vec<2, T> zero;
		static const vec<2, T> up;
		static const vec<2, T> right;
	};

	template<typename T> const vec<2, T> tvec2<T>::zero = tvec2<T>(0.0, 0.0);
	template<typename T> const vec<2, T> tvec2<T>::up = tvec2<T>(0.0, 1.0);
	template<typename T> const vec<2, T> tvec2<T>::right = tvec2<T>(1.0, 0.0);
	
	template<typename T>
	struct tvec3 : public vec<3, T>
	{
		float& x = data[0];
		float& y = data[1];
		float& z = data[2];
		
		tvec3() : vec<3, T>() {}
		tvec3(T _x, T _y, T _z) {
			data[0] = _x;
			data[1] = _y;
			data[2] = _z;
		}
		tvec3(const vec<3, T>& v) {
			data = v.data;
		}
		tvec3(const T& value) : vec<3, T>(value) {}
		tvec3(const std::initializer_list<T> args) : vec<3, T>(args) {}

		tvec3(const vec<2, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = T{};
		}

		/* cross product */
		tvec3 cross(const tvec3 v) const {
			return tvec3(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x
			);
		}

		static tvec3 cross(const tvec3& v, const tvec3& w) {
			return tvec3<T>(
				v.y*w.z - v.z*w.y,
				v.z*w.x - v.x*w.z,
				v.x*w.y - v.y*w.x
			);
		}

		/* scalar triple product */
		float triple(const tvec3& v, const tvec3& w) const {
			return ((*this).cross(v))*w;
		}

		/* scalar triple product */
		static float triple(const tvec3& v1, const tvec3& v2, const tvec3<T>& v3) {
			return (v1.cross(v2))*v3;
		}

		tvec3<T>& operator= (const vec<3, T>& v) {
			data = v.data;
			return *this;
		}

		static const vec<3, T> zero;
		static const vec<3, T> up;
		static const vec<3, T> right;
		static const vec<3, T> forward;
	}; 
	
	template<typename T> const vec<3, T> tvec3<T>::zero = tvec3<T>(0.0, 0.0, 0.0);
	template<typename T> const vec<3, T> tvec3<T>::up = tvec3<T>(0.0, 1.0, 0.0);
	template<typename T> const vec<3, T> tvec3<T>::right = tvec3<T>(1.0, 0.0, 0.0);
	template<typename T> const vec<3, T> tvec3<T>::forward = tvec3<T>(0.0, 0.0, -1.0);

	template<typename T>
	struct tvec4 : public vec<4, T>
	{
		float& x = data[0];
		float& y = data[1];
		float& z = data[2];
		float& w = data[3];

		tvec4() : vec<4, T>() {}
		tvec4(T _x, T _y, T _z, T _w) {
			data[0] = _x;
			data[1] = _y;
			data[2] = _z;
			data[3] = _w;
		}
		tvec4(const vec<4, T>& v) {
			data = v.data;
		}
		tvec4(const T& value) : vec<4, T>(value) {}
		tvec4(const std::initializer_list<T> args) : vec<4, T>(args) {}

		tvec4(const vec<2, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = T{};
			data[3] = T{};
		}
		tvec4(const vec<3, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = v[2];
			data[3] = T{};
		}

		tvec4<T>& operator= (const vec<4, T>& v) {
			data = v.data;
			return *this;
		}

		static const vec<4, T> zero;
	};

	template<typename T> const vec<4, T> tvec4<T>::zero = tvec4<T>(0.0, 0.0, 0.0, 0.0);

	typedef tvec2<float> vec2;
	typedef tvec3<float> vec3;
	typedef tvec4<float> vec4;
	typedef vec2 vector2;
	typedef vec3 vector3;
	typedef vec4 vector4;

	typedef vec2 fvec2;
	typedef vec3 fvec3;
	typedef vec4 fvec4;
	typedef vector2 fvector2;
	typedef vector3 fvector3;
	typedef vector4 fvector4;

	typedef tvec2<double> dvec2;
	typedef tvec3<double> dvec3;
	typedef tvec4<double> dvec4;
	typedef dvec2 dvector2;
	typedef dvec3 dvector3;
	typedef dvec4 dvector4;

	typedef tvec2<int> ivec2;
	typedef tvec3<int> ivec3;
	typedef tvec4<int> ivec4;
	typedef ivec2 ivector2;
	typedef ivec3 ivector3;
	typedef ivec4 ivector4;

	typedef tvec2<unsigned int> uvec2;
	typedef tvec3<unsigned int> uvec3;
	typedef tvec4<unsigned int> uvec4;
	typedef uvec2 uvector2;
	typedef uvec3 uvector3;
	typedef uvec4 uvector4;

	typedef tvec2<bool> bvec2;
	typedef tvec3<bool> bvec3;
	typedef tvec4<bool> bvec4;
	typedef bvec2 bvector2;
	typedef bvec3 bvector3;
	typedef bvec4 bvector4;
};