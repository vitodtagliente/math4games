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

		static T magnitude(const vector<n, T>& v) {
			return v.magnitude();
		}

		T distance(const vector<n, T>& other) const {
			return (*this - other).magnitude();
		}

		static T distance(const vector<n, T>& v, const vector<n, T>& w) {
			return (v - w).magnitude();
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

	template<typename T>
	struct tvector2 : public vector<2, T>
	{
		float& x = data[0];
		float& y = data[1];

		tvector2() : vector<2, T>() {}
		tvector2(T _x, T _y) {
			data[0] = _x;
			data[1] = _y;
		}
		tvector2(const vector<2, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
		}
		tvector2(const T& value) : vector<2, T>(value) {}
		tvector2(const std::initializer_list<T> args) : vector<2, T>(args) {}

		tvector2<T>& operator= (const vector<2, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			return *this;
		}

		static const vector<2, T> zero;
		static const vector<2, T> up;
		static const vector<2, T> right;
	};

	template<typename T> const vector<2, T> tvector2<T>::zero = tvector2<T>(0.0, 0.0);
	template<typename T> const vector<2, T> tvector2<T>::up = tvector2<T>(0.0, 1.0);
	template<typename T> const vector<2, T> tvector2<T>::right = tvector2<T>(1.0, 0.0);
	
	template<typename T>
	struct tvector3 : public vector<3, T>
	{
		float& x = data[0];
		float& y = data[1];
		float& z = data[2];
		
		tvector3() : vector<3, T>() {}
		tvector3(T _x, T _y, T _z) {
			data[0] = _x;
			data[1] = _y;
			data[2] = _z;
		}
		tvector3(const vector<3, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = v[2];
		}
		tvector3(const T& value) : vector<3, T>(value) {}
		tvector3(const std::initializer_list<T> args) : vector<3, T>(args) {}

		/* cross product */
		tvector3 cross(const tvector3 v) const {
			return tvector3(
				y*v.z - z*v.y,
				z*v.x - x*v.z,
				x*v.y - y*v.x
			);
		}

		static tvector3 cross(const tvector3& v, const tvector3& w) {
			return tvector3<T>(
				v.y*w.z - v.z*w.y,
				v.z*w.x - v.x*w.z,
				v.x*w.y - v.y*w.x
			);
		}

		/* scalar triple product */
		float triple(const tvector3& v, const tvector3& w) const {
			return ((*this).cross(v))*w;
		}

		/* scalar triple product */
		static float triple(const tvector3& v1, const tvector3& v2, const tvector3<T>& v3) {
			return (v1.cross(v2))*v3;
		}

		tvector3<T>& operator= (const vector<3, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = v[2];
			return *this;
		}

		static const vector<3, T> zero;
		static const vector<3, T> up;
		static const vector<3, T> right;
		static const vector<3, T> forward;
	}; 
	
	template<typename T> const vector<3, T> tvector3<T>::zero = tvector3<T>(0.0, 0.0, 0.0);
	template<typename T> const vector<3, T> tvector3<T>::up = tvector3<T>(0.0, 1.0, 0.0);
	template<typename T> const vector<3, T> tvector3<T>::right = tvector3<T>(1.0, 0.0, 0.0);
	template<typename T> const vector<3, T> tvector3<T>::forward = tvector3<T>(0.0, 0.0, -1.0);

	template<typename T>
	struct tvector4 : public vector<4, T>
	{
		float& x = data[0];
		float& y = data[1];
		float& z = data[2];
		float& w = data[3];

		tvector4() : vector<4, T>() {}
		tvector4(T _x, T _y, T _z, T _w) {
			data[0] = _x;
			data[1] = _y;
			data[2] = _z;
			data[3] = _w;
		}
		tvector4(const vector<4, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = v[2];
			data[3] = v[3];
		}
		tvector4(const T& value) : vector<4, T>(value) {}
		tvector4(const std::initializer_list<T> args) : vector<4, T>(args) {}

		tvector4<T>& operator= (const vector<4, T>& v) {
			data[0] = v[0];
			data[1] = v[1];
			data[2] = v[2];
			data[3] = v[3];
			return *this;
		}

		static const vector<4, T> zero;
	};

	template<typename T> const vector<4, T> tvector4<T>::zero = tvector4<T>(0.0, 0.0, 0.0, 0.0);
		
	typedef tvector2<float> vector2;
	typedef tvector3<float> vector3;
	typedef tvector4<float> vector4;
	typedef vector2 vec2;
	typedef vector3 vec3;
	typedef vector4 vec4;

	typedef tvector2<double> dvector2;
	typedef tvector3<double> dvector3;
	typedef tvector4<double> dvector4;
	typedef dvector2 dvec2;
	typedef dvector3 dvec3;
	typedef dvector4 dvec4;

	typedef tvector2<int> ivector2;
	typedef tvector3<int> ivector3;
	typedef tvector4<int> ivector4;
	typedef ivector2 ivec2;
	typedef ivector3 ivec3;
	typedef ivector4 ivec4;
};