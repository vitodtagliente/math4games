#pragma once

#include <cassert>
#include <initializer_list>

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

		T determinant() {
			/* must be square matrix */
			assert(n == m && n > 0 && m > 0);

			if (n == 1)
				return data[0][0];
			else if (n == 2)
				return data[0][0] * data[1][1] - (data[0][1] * data[1][0]);
			else if (n == 3) {
				/* Sarrus law */
				return (data[0][0] * data[1][1] * data[2][2]) -
					(data[0][1] * data[1][2] * data[2][0]) -
					(data[0][2] * data[1][0] * data[2][1]);
			}
			else {
				/* Laplace law */
				int j = 0;
				T result{};
				for (int i = 0; i < m; i++) {
					assert(n > 0 && m > 0);
					matrix<n - 1, m - 1, T> currentMinor = minor(i, j);
					/* TODO? fix this compile error
					if (i + j % 2 != 0)
					result -= currentMinor.determinant();
					else result += currentMinor.determinant();
					*/
				}
				return result;
			}
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
					result.data[j][i] = currentMinor.determinant();
					if (i + j % 2 != 0)
						result.data[j][i] = -result.data[j][i];
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

	/* matrix x column vector operation */
	template<std::size_t n, std::size_t m, typename T>
	vector<n, T> operator* (const matrix<n, m, T>& M, const vector<m, T>& v) {
		vector<n, T> result;
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

	typedef tmatrix2<double> matrix2d;
	typedef tmatrix3<double> matrix3d;
	typedef tmatrix4<double> matrix4d;
	typedef matrix2d mat2d;
	typedef matrix3d mat3d;
	typedef matrix4d mat4d;

	typedef tmatrix2<int> matrix2i;
	typedef tmatrix3<int> matrix3i;
	typedef tmatrix4<int> matrix4i;
	typedef matrix2i mat2i;
	typedef matrix3i mat3i;
	typedef matrix4i mat4i;
};
