#pragma once

#include <cmath>

class vector4 
{

private:

public:

	float x, y, z, w;

	vector4() = default;

	vector4(float value) {
		x = y = z = w = value;
	}

	vector4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	vector4(const vector4& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	~vector4() {}

	float magnitude() {
		return sqrt(x*x + y*y + z*z + w*w);
	}

	vector4 normalize() {
		return (*this / magnitude());
	}

	float dot(const vector4& v) {
		return (x*v.x + y*v.y + z*v.z + w*v.w);
	}

	/* Operators overloading */

	vector4& operator=(const vector4& other) {
		// check for self-assignment
		if (this == &other)
			return *this;

		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	vector4& operator+=(const vector4& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	vector4 operator+(const vector4& other) {
		return vector4(*this) += other;
	}

	vector4& operator-=(const vector4& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vector4 operator-(const vector4& other) {
		return vector4(*this) -= other;
	}

	vector4 operator-() {
		return (*this) * -1;
	}

	vector4& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	vector4 operator*(float s) {
		return vector4(*this) *= s;
	}

	vector4& operator/=(float s) {
		s = 1.0f / s;
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	vector4 operator/(float s) {
		return vector4(*this) /= s;
	}

	bool operator==(const vector4& other) {
		return x == other.x &&
			y == other.y &&
			z == other.z &&
			w == other.w;
	}

	bool operator!=(const vector4& other) {
		return !(*this == other);
	}

};