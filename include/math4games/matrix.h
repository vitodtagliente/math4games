#pragma once

#include <cmath>
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
			for (auto& it : args)
			{
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
			return T{}; // TODO
		}

		static T determinant(matrix<n, m, T> M) {
			return M.determinant();
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

		static matrix<m, n, T> transpose(const matrix<n, m, T>& M) {
			return M.transpose();
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

		static matrix<n, m, T> inverse(const matrix<n, m, T>& M, bool& invertible) {
			return M.inverse(invertible);
		}

		matrix<n, m, T> adjugate() {
			return *this; // TODO
		}

		static matrix<n, m, T> adjugate(const matrix<n, m, T>& M) {
			return M.adjugate();
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
		
		T determinant() {
			return data[0][0] * data[1][1] - (data[0][1] * data[1][0]);
		}
		
		tmatrix2 adjugate() {
			return tmatrix2(
				data[1][1], -data[0][1],
				-data[1][0], data[0][0]
			);
		}

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

	typedef tmatrix2<float> matrix2;
	typedef matrix2 m2;
};