#pragma once

#include <cmath>
#include <assert.h>

namespace math4games
{
	template<class T>
	struct tvector2
	{
		T x, y;

		tvector2<T>() = default;

		tvector2<T>(T value) {
			x = y = value;
		}

		tvector2<T>(T _x, T _y) {
			x = _x;
			y = _y;
		}

		tvector2<T>(const tvector2<T>& other) {
			x = other.x;
			y = other.y;
		}

		~tvector2<T>() {}

		tvector2<T>& set(T _x, T _y) {
			x = _x;
			y = _y;
			return (*this);
		}

		static tvector2<T> zero() {
			return tvector2<T>(0.0f, 0.0f);
		}

		T magnitude() const {
			return sqrt(x*x + y*y);
		}

		tvector2<T>& normalize() {
			return (*this *= (1.0f / magnitude()));
		}

		T distance(const tvector2<T>& v) const {
			return (*this - v).magnitude();
		}

		static T distance(const tvector2<T>& v1, const tvector2<T>& v2) {
			return (v1 - v2).magnitude();
		}

		T dot(const tvector2<T>& v) const {
			return (*this)*v;
		}

		static T dot(const tvector2<T>& v1, const tvector2<T>& v2) {
			return v1*v2;
		}

		tvector2<T> project(const tvector2<T>& v) {
			return v* ((*this*v) / (v*v));
		}

		static tvector2<T> project(const tvector2<T>& v1, const tvector2<T>& v2) {
			return v2* ((v1*v2) / (v2*v2));
		}
		
		tvector2<T> reject(const tvector2<T>& v) {
			return (*this - v)* ((*this*v) / (v*v));
		}

		static tvector2<T> reject(const tvector2<T>& v1, const tvector2<T>& v2) {
			return (v1 - v2)* ((v1*v2) / (v2*v2));
		}
		
		/* Operators overloading */

		T& operator[](int i){
			assert(i >= 0 && i < 2);
			return ((&x)[i]);
		}

		const T operator[](int i) const {
			if (i >= 2)
				return 0.0f;
			return ((&x)[i]);
		}

		tvector2<T>& operator=(const tvector2<T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			x = other.x;
			y = other.y;
			return *this;
		}

		tvector2<T>& operator+=(const tvector2<T>& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		tvector2<T>& operator-=(const tvector2<T>& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		tvector2<T>& operator*=(const T s) {
			x *= s;
			y *= s;
			return *this;
		}

		tvector2<T>& operator/=(const T s) {
			T f = 1.0f / s;
			x *= f;
			y *= f;
			return *this;
		}

		bool operator==(const tvector2<T>& other) const {
			return x == other.x &&
				y == other.y;
		}

		bool operator!=(const tvector2<T>& other) const {
			return !(*this == other);
		}

		tvector2<T> operator-() const {
			return tvector2<T>(-x, -y);
		}

		tvector2<T> operator+(const tvector2<T>& v) const {
			return tvector2<T>(x + v.x, y + v.y);
		}

		tvector2<T> operator-(const tvector2<T>& v) const {
			return tvector2<T>(x - v.x, y - v.y);
		}

		tvector2<T> operator*(const T s) const {
			return tvector2<T>(x * s, y * s);
		}

		tvector2<T> operator/(const T s) const {
			T f = 1.0f / s;
			return tvector2<T>(x * f, y * f);
		}

		/* dot product */
		T operator*(const tvector2<T>& v) const {
			return (x*v.x + y*v.y);
		}
		
	};

	template<class T>
	inline tvector2<T> operator*(const T s, const tvector2<T>& v) {
		return tvector2<T>(v.x * s, v.y * s);
	}

	typedef tvector2<float> vector2;
	typedef tvector2<double> dvector2;
	typedef tvector2<int> ivector2;
};