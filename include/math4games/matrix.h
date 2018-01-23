#pragma once

/*
matrix implementation using row major representation
credits: Vito Domenico Tagliente
*/

#include <cassert>
#include <initializer_list>
#include <array>

#include "vector.h"

namespace math4games
{
	/*
	n: num of rows
	m: num of columns
	*/
	template<std::size_t n, std::size_t m, class T>
	struct matrix
	{
		T data[n][m];
		const int rows = n;
		const int columns = m;

		matrix() {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] = {};
		}

		matrix(const T& value) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] = value;
		}

		matrix(const std::initializer_list<T> args) {
			assert(args.size() <= m*n);
			int i = 0, j = 0;
			for (auto& it : args) {
				data[j][i++] = it;
				if (i >= n) {
					++j;
					i = 0;
				}
			}
		}

		T& operator() (int i, int j) {
			assert(i < m && j < n);
			return data[j][i];
		}

		const T& operator() (int i, int j) const {
			assert(i < m && j < n);
			return data[j][i];
		}

		matrix<n, m, T> identity() {
			/* check if it is square matrix */
			assert(n == m);

			matrix<n, m, T> M(0);
			for (i = 0; i < n; i++) {
				data[i][i] = 1.0;
			}
		}

		virtual T determinant() {
			return T{};
		}
				
		matrix<n - 1, m - 1, T> minor(int x, int y) {
			matrix<n - 1, m - 1, T> result;
			for (int j = 0; j < n; j++) {
				for (int i = 0; i < m; i++) {
					if (i != x && j != y)
						result.data[(j > y) ? j - 1 : j][(i > x) ? i - 1 : i] = data[j][i];
				}
			}
			return result;
		}

		matrix<m, n, T> transpose() {
			matrix<m, n, T> MT;
			for (int j = 0; j < n; j++) {
				for (int i = 0; i < m; i++) {
					MT.data[i][j] = data[j][i];
				}
			}
			return MT;
		}

		matrix<n, m, T> inverse(bool& invertible) {
			invertible = false;
			float d = determinant();
			if (d != 0.0f) {
				invertible = true;
				return adjugate() / d;
			}
			return *this;
		}

		matrix<n, m, T> adjugate() {
			matrix<n, m, T> result;
			for (int j = 0; j < n; j++) {
				for (int i = 0; i < m; i++) {
					matrix<n - 1, m - 1, T> currentMinor = minor(i, j);
					result.data[j][i] = std::pow(-1, i + 1)*currentMinor.determinant();
				}
			}
			return result;
		}

		/* Operators overloading */

		matrix<n, m, T>& operator= (const matrix<n, m, T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] = other.data[i][j];
			return *this;
		}

		bool operator== (const matrix<n, m, T>& other) const {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					if (data[i][j] != other.data[i][j])
						return false;
			return true;
		}

		bool operator!= (const matrix<n, m, T>& other) const {
			return !(*this == other);
		}

		matrix<n, m, T>& operator+= (const matrix<n, m, T>& other) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] += other.data[i][j];
			return *this;
		}

		matrix<n, m, T>& operator-= (const matrix<n, m, T>& other) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] -= other.data[i][j];
			return *this;
		}

		matrix<n, m, T>& operator*= (const T s) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] *= s;
			return *this;
		}

		matrix<n, m, T>& operator/= (const T s) {
			T f = 1.0f / s;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					data[i][j] *= f;
			return *this;
		}

		matrix<n, m, T> operator- () const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = -data[i][j];
			return result;
		}

		matrix<n, m, T> operator+ (const matrix<n, m, T>& other) const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] + other.data[i][j];
			return result;
		}

		matrix<n, m, T> operator- (const matrix<n, m, T>& other) const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] - other.data[i][j];
			return result;
		}

		matrix<n, m, T> operator* (const T s) const {
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] * s;
			return result;
		}

		matrix<n, m, T> operator/ (const T s) const {
			T f = 1.0f / s;
			matrix<n, m, T> result;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					result.data[i][j] = data[i][j] * f;
			return result;
		}
	};

	/* matrix x matrix operation */
	template<std::size_t n, std::size_t m, std::size_t o, typename T>
	matrix<n, o, T> operator* (const matrix<n, m, T>& m1, const matrix<m, o, T>& m2) {
		matrix<n, o, T> result;
		for (int j = 0; j < n; j++) {
			for (int y = 0; y < o; y++) {
				T value{};
				for (int i = 0; i < n; i++) {
					value += m1.data[j][i] * m2.data[i][y];
				}
				result.data[j][y] = value;
			}
		}
		return result;
	}

	/* matrix x column vec operation */
	template<std::size_t n, std::size_t m, typename T>
	vec<n, T> operator* (const matrix<n, m, T>& M, const vec<m, T>& v) {
		vec<n, T> result;
		for (int j = 0; j < n; j++) {
			T value{};
			for (int i = 0; i < m; i++) {
				value += M.data[j][i] * v.data[i];
			}
			result.data[j] = value;
		}
		return result;
	}

	template<typename T>
	struct tmatrix2 : public matrix<2, 2, T>
	{
		tmatrix2() : matrix<2, 2, T>() {}

		tmatrix2(
			const T& a00, const T& a10,
			const T& a01, const T& a11
		) {
			data[0][0] = a00; data[0][1] = a10;
			data[1][0] = a01; data[1][1] = a11;
		}
		tmatrix2(const matrix<2, 2, T>& m) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					data[i][j] = m.data[i][j];
		}
		tmatrix2(const T& value) : matrix<2, 2, T>(value) {}
		tmatrix2(const std::initializer_list<T> args) : matrix<2, 2, T>(args) {}
		
		tmatrix2<T>& operator= (const matrix<2, 2, T>& m) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					data[i][j] = m.data[i][j];
			return *this;
		}

		T determinant() override {
			return data[0][0] * data[1][1] - (data[0][1] * data[1][0]);
		}

		static tmatrix2<float> rotate(const float theta) {
			return tmatrix2<float>(
				std::cos(theta), std::sin(theta),
				-std::sin(theta), std::cos(theta)
			);
		}

		static tmatrix2<float> scale(const float scale_x, const float scale_y) {
			return tmatrix2<float>(
				scale_x, 0,
				0, scale_y
			);
		}

		static tmatrix2<float> scale(const vec2& v) {
			return tmatrix2<float>(
				v.x, 0,
				0, v.y
			);
		}

		static const matrix<2, 2, T> zero;
		static const matrix<2, 2, T> identity;
	};

	template<typename T> const matrix<2, 2, T> tmatrix2<T>::zero = tmatrix2<T>(0.0, 0.0, 0.0, 0.0);
	template<typename T> const matrix<2, 2, T> tmatrix2<T>::identity = tmatrix2<T>(1.0, 0.0, 0.0, 1.0);

	template<typename T>
	struct tmatrix3 : public matrix<3, 3, T>
	{
		tmatrix3() : matrix<3, 3, T>() {}

		tmatrix3(
			const T& a00, const T& a10, const T& a20,
			const T& a01, const T& a11, const T& a21,
			const T& a02, const T& a12, const T& a22
		) {
			data[0][0] = a00; data[0][1] = a10; data[0][2] = a20;
			data[1][0] = a01; data[1][1] = a11; data[1][2] = a21;
			data[2][0] = a02; data[2][1] = a12; data[2][2] = a22;
		}
		tmatrix3(const matrix<3, 3, T>& m) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					data[i][j] = m.data[i][j];
		}
		tmatrix3(const T& value) : matrix<3, 3, T>(value) {}
		tmatrix3(const std::initializer_list<T> args) : matrix<3, 3, T>(args) {}
				
		tmatrix3<T>& operator= (const matrix<3, 3, T>& m) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					data[i][j] = m.data[i][j];
			return *this;
		}

		T determinant() override {
			/* Sarrus law */
			return (data[0][0] * data[1][1] * data[2][2]) -
				(data[0][1] * data[1][2] * data[2][0]) -
				(data[0][2] * data[1][0] * data[2][1]);
		}

		static tmatrix3<float> rotateX(const float delta_x, const float delta_y) {
			return matrix3<float>(
				1, 0, 0,
				0, 1, 0,
				delta_x, delta_y, 1
			);
		}

		static tmatrix3<float> rotateX(const vec2& v) {
			return matrix3<float>(
				1, 0, 0,
				0, 1, 0,
				v.x, v.y, 1
			);
		}

		static tmatrix3<float> rotateX(const float theta) {
			return matrix3<float>(
				1, 0, 0,
				0, std::cos(theta), -std::sin(theta),
				0, std:sin(theta), std::cos(theta)
			);
		}

		static tmatrix3<float> rotateY(const float theta) {
			return tmatrix3<float>(
				std::cos(theta), 0, std::sin(theta),
				0, 1, 0,
				-std::sin(theta), 0, std::cos(theta)
			);
		}

		static tmatrix3<float> rotateZ(const float theta) {
			return tmatrix3<float>(
				std::cos(theta), -std::sin(theta), 0,
				std::sin(theta), std::cos(theta), 0,
				0, 0, 1
			);
		}

		static tmatrix3<float> rotate(const vec3& v, const float theta) {
			return tmatrix3 <float>(); // TODO: to be implemented
		}

		static tmatrix3<float> scale(const float scale_x, const float scale_y, const float scale_z) {
			return tmatrix3<float>(
				scale_x, 0, 0,
				0, scale_y, 0,
				0, 0, scale_z
			);
		}

		static tmatrix3<float> scale(const vec3& v) {
			return tmatrix3<float>(
				v.x, 0, 0,
				0, v.y, 0,
				0, 0, v.z
			);
		}

		static const matrix<3, 3, T> zero;
		static const matrix<3, 3, T> identity;
	};

	template<typename T> const matrix<3, 3, T> tmatrix3<T>::zero = tmatrix3<T>(0.0);
	template<typename T> const matrix<3, 3, T> tmatrix3<T>::identity = tmatrix3<T>(
		1.0, 0.0, 0.0, 
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	);

	template<typename T>
	struct tmatrix4 : public matrix<4, 4, T>
	{
		tmatrix4() : matrix<4, 4, T>() {}

		tmatrix4(
			const T& a00, const T& a10, const T& a20, const T& a30,
			const T& a01, const T& a11, const T& a21, const T& a31,
			const T& a02, const T& a12, const T& a22, const T& a32,
			const T& a03, const T& a13, const T& a23, const T& a33
		) {
			data[0][0] = a00; data[0][1] = a10; data[0][2] = a20; data[0][3] = a30;
			data[1][0] = a01; data[1][1] = a11; data[1][2] = a21; data[1][3] = a31;
			data[2][0] = a02; data[2][1] = a12; data[2][2] = a22; data[2][3] = a32;
			data[3][0] = a03; data[3][1] = a13; data[3][2] = a23; data[3][3] = a33;
		}
		tmatrix4(const matrix<4, 4, T>& m) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					data[i][j] = m.data[i][j];
		}
		tmatrix4(const T& value) : matrix<4, 4, T>(value) {}
		tmatrix4(const std::initializer_list<T> args) : matrix<4, 4, T>(args) {}
		
		tmatrix4<T>& operator= (const matrix<4, 4, T>& m) {
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < columns; j++)
					data[i][j] = m.data[i][j];
			return *this;
		}

		T determinant() override {
			/* Laplace law */
			int j = 0;
			T result{};
			for (int i = 0; i < m; i++) {
				auto currentMinor = M->minor(i, j);
				result += std::pow(-1, i + j)*currentMinor.determinant();
			}
			return result;
		}

		static tmatrix4<float> rotateX(const float delta_x, const float delta_y, const float delta_z) {
			return matrix4<float>(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				delta_x, delta_y, delta_z, 1
			);
		}

		static tmatrix4<float> rotateX(const vec3& v) {
			return matrix4<float>(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				v.x, v.y, v.z, 1
			);
		}

		static const matrix<4, 4, T> zero;
		static const matrix<4, 4, T> identity;
	};

	template<typename T> const matrix<4, 4, T> tmatrix4<T>::zero = tmatrix4<T>(0.0);
	template<typename T> const matrix<4, 4, T> tmatrix4<T>::identity = tmatrix4<T>(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	typedef tmatrix2<float> matrix2;
	typedef tmatrix3<float> matrix3;
	typedef tmatrix4<float> matrix4;
	typedef matrix2 mat2;
	typedef matrix3 mat3;
	typedef matrix4 mat4;

	typedef matrix2 fmatrix2;
	typedef matrix3 fmatrix3;
	typedef matrix4 fmatrix4;
	typedef mat2 fmat2;
	typedef mat3 fmat3;
	typedef mat4 fmat4;

	typedef tmatrix2<double> dmatrix2;
	typedef tmatrix3<double> dmatrix3;
	typedef tmatrix4<double> dmatrix4;
	typedef dmatrix2 dmat2;
	typedef dmatrix3 dmat3;
	typedef dmatrix4 dmat4;
};
