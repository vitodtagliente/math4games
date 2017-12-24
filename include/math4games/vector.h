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
			data.fill(value);
		}

		vector(const std::initializer_list<T> args) {
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

		T dot(const vector<n, T>& other) const {
			return (*this)*other;
		}

		static T dot(const vector<n, T>& v, const vector<n, T>& w) {
			return v*w;
		}

		vector<n, T> normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		vector<n, T> project(const vector<n, T>& v) {
			return v* ((*this*v) / (v*v));
		}

		static vector<n, T> project(const vector<n, T>& v, const vector<n, T>& w) {
			return w* ((v*w) / (v*w));
		}

		vector<n, T> reject(const vector<n, T>& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}

		static vector<n, T> reject(const vector<n, T>& v, const vector<n, T>& w) {
			return (v - w)* ((v*w) / (v*w));
		}

		/* Operators overloading */

		vector<n, T>& operator= (const vector<n, T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			for (std::size_t i = 0; i < n; i++)
				data[i] = other[i];
			return *this;
		}

		bool operator== (const vector<n, T>& other) const {
			return (*this).data == other.data;
		}

		bool operator!= (const vector<n, T>& other) const {
			return !(*this == other);
		}

		vector<n, T>& operator+= (const vector<n, T>& other) {
			for (std::size_t i = 0; i < n; i++)
				data[i] += other[i];
			return *this;
		}

		vector<n, T>& operator-= (const vector<n, T>& other) {
			for (std::size_t i = 0; i < n; i++)
				data[i] -= other[i];
			return *this;
		}

		vector<n, T>& operator*= (const T s) {
			for (std::size_t i = 0; i < n; i++)
				data[i] *= s;
			return *this;
		}

		vector<n, T>& operator/= (const T s) {
			T f = 1.0f / s;
			for (std::size_t i = 0; i < n; i++)
				data[i] *= f;
			return *this;
		}

		vector<n, T> operator- () const {
			vector<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = -data[i];
			return v;
		}

		vector<n, T> operator+ (const vector<n, T>& w) const {
			vector<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] + w[i];
			return v;
		}

		vector<n, T> operator- (const vector<n, T>& w) const {
			vector<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] - w[i];
			return v;
		}

		vector<n, T> operator* (const T s) const {
			vector<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] * s;
			return v;
		}

		vector<n, T> operator/ (const T s) const {
			T f = 1.0f / s;
			vector<n, T> v;
			for (std::size_t i = 0; i < n; i++)
				v[i] = data[i] * f;
			return v;
		}

		/* dot product */
		T operator*(const vector<n, T>& v) const {
			T dot{};
			for (std::size_t i = 0; i < n; i++)
				dot += data[i] * w[i];
			return dot;
		}
	};

	template<std::size_t n, class T>
	inline vector<n, T> operator* (const T s, const vector<n, T>& v) {
		vector<n, T> w;
		for (std::size_t i = 0; i < n; i++)
			w[i] = v[i] * s;
		return w;
	}

	template<class T>
	struct vec2 : public vector<2, T>
	{
		float& x = data[0];
		float& y = data[1];

		vec2() : vector<2, T>() {}
		vec2(T _x, T _y) {
			data[0] = _x;
			data[1] = _y;
		}

		vec2(const T& value) : vector<2, T>(value) {}
		vec2(const std::initializer_list<T> args) : vector<2, T>(args) {}
	};
	
	template<class T>
	struct vec3 : public vector<3, T>
	{
		float& x = data[0];
		float& y = data[1];
		float& z = data[2];
		
		vec3() : vector<3, T>() {}
		vec3(T _x, T _y, T _z) {
			data[0] = _x;
			data[1] = _y;
			data[2] = _z;
		}

		vec3(const T& value) : vector<3, T>(value) {}
		vec3(const std::initializer_list<T> args) : vector<3, T>(args) {}

		/* cross product */
		vec3 cross(const vec3 v) const {
			return vec3(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x
			);
		}

		static vec3 cross(const vec3& v, const vec3& w) {
			return tvector3<T>(
				v.y*w.z - v.z*w.y,
				v.z*w.x - v.x*w.z,
				v.x*w.y - v.y*w.x
			);
		}

		/* scalar triple product */
		float triple(const vec3& v, const vec3& w) const {
			return ((*this).cross(v))*w;
		}

		/* scalar triple product */
		static float triple(const vec3& v1, const vec3& v2, const vec3<T>& v3) {
			return (v1.cross(v2))*v3;
		}
	};

	template<class T>
	struct vec4 : public vector<4, T>
	{
		float& x = data[0];
		float& y = data[1];
		float& z = data[2];
		float& w = data[3];

		vec4() : vector<4, T>() {}
		vec4(T _x, T _y, T _z, T _w) {
			data[0] = _x;
			data[1] = _y;
			data[2] = _z;
			data[3] = _w;
		}

		vec4(const T& value) : vector<4, T>(value) {}
		vec4(const std::initializer_list<T> args) : vector<4, T>(args) {}
	};
		
	typedef vec2<float> vector2;

};