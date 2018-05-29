#pragma once

/*
	Matrix math representation
	Vito Domenico Tagliente
	math library for games
*/

#include "vector.h"

namespace math4games
{
	template<std::size_t N, std::size_t M, class T>
	struct base_matrix
	{
		// num of rows
		const std::size_t rows = N;
		// num of columns
		const std::size_t columns = M;

		// store data into a managed array
		std::array<T, N * M> data;

		// default constructor
		base_matrix() {
			data.fill(T{});
		}

		// this constructor fill all components with the same value
		base_matrix(const T value) {
			data.fill(value);
		}

		// construct with initialzie list
		base_matrix(const std::initializer_list<T>& args) {
			unsigned int i = 0;
			for (auto begin = args.begin(); begin != args.end() && i < N * M; ++begin) {
				data[i] = *begin;
				++i;
			}
		}

		// copy constructor
		base_matrix(const base_matrix<N, M, T>& other)
		{
			data = other.data;
		}

		T& operator() (const std::size_t i, const std::size_t j) {
			assert(i < columns && j < rows);
			return data[i + j * columns];
		}

		const T& operator() (const std::size_t i, const std::size_t j) const {
			assert(i < columns && j < rows);
			return data[i + j * columns];
		}
		
		// determinant 
		T determinant() const
		{
			return determinant_algorithm(*this);
		}

		// sub matrix
		base_matrix<N - 1, M - 1, T> minor(const std::size_t x, const std::size_t y) const {
			assert(x < columns && y < rows);
			base_matrix<N - 1, M - 1, T> result;

			for (int j = 0, _j = 0; j < N; ++j)
			{
				if (j == y) continue;
				for (int i = 0, _i = 0; i < M; ++i)
				{
					if (i == x) continue;
					result(_i, _j) = (*this)(i, j);
					++_i;
				}
				++_j;
			}
			return result;
		}

		// transpose matrix
		base_matrix<M, N, T> transpose() {
			base_matrix<M, N, T> MT;
			for (int j = 0; j < N; j++) {
				for (int i = 0; i < M; i++) {
					MT(i, j) = (*this)(j, i);
				}
			}
			return MT;
		}

		// inverse matrix
		base_matrix<N, M, T> inverse(bool& invertible) {
			invertible = false;
			T d = determinant(*this);
			if (d != static_cast<T>(0.0)) {
				invertible = true;
				return adjugate() / d;
			}
			return *this;
		}

		// adjugate matrix
		base_matrix<N, M, T> adjugate() {
			base_matrix<N, M, T> result;
			for (int j = 0; j < N; ++j) {
				for (int i = 0; i < M; ++i) {
					base_matrix<N - 1, M - 1, T> currentMinor = minor(i, j);
					result(j, i) = static_cast<T>(std::pow(-1, i + 1))*currentMinor.determinant();
				}
			}
			return result;
		}

		/* Operators overloading */

		base_matrix<N, M, T>& operator= (const base_matrix<N, M, T>& other) {
			// check for self-assignment
			if (this == &other)
				return *this;

			data = other.data;

			return *this;
		}

		bool operator== (const base_matrix<N, M, T>& other) const {
			return (*this).data == other.data;
		}

		bool operator!= (const base_matrix<N, M, T>& other) const {
			return !(*this == other);
		}

		base_matrix<N, M, T>& operator+= (const base_matrix<N, M, T>& other) {
			for (int i = 0; i < data.size(); i++)
				data[i] += other.data[i];
			return *this;
		}

		base_matrix<N, M, T>& operator-= (const base_matrix<N, M, T>& other) {
			for (int i = 0; i < data.size(); i++)
				data[i] -= other.data[i];
			return *this;
		}

		base_matrix<N, M, T>& operator*= (const T s) {
			for (int i = 0; i < data.size(); i++)
				data[i] *= s;
			return *this;
		}

		base_matrix<N, M, T>& operator/= (const T s) {
			T f = static_cast<T>(1.0f / s);
			return (*this) *= f;
		}

		base_matrix<N, M, T> operator- () const {
			base_matrix<N, M, T> result;
			for (int i = 0; i < data.size(); i++)
				result.data[i] = -data[i];
			return result;
		}

		base_matrix<N, M, T> operator+ (const base_matrix<N, M, T>& other) const {
			base_matrix<N, M, T> result;
			for (int i = 0; i < data.size(); i++)
				result.data[i] = data[i] + other.data[i];
			return result;
		}

		base_matrix<N, M, T> operator- (const base_matrix<N, M, T>& other) const {
			base_matrix<N, M, T> result;
			for (int i = 0; i < data.size(); i++)
				result.data[i] = data[i] - other.data[i];
			return result;
		}

		base_matrix<N, M, T> operator* (const T s) const {
			base_matrix<N, M, T> result;
			for (int i = 0; i < data.size(); i++)
				result.data[i] = data[i] * s;
			return result;
		}

		base_matrix<N, M, T> operator/ (const T s) const {
			T f = static_cast<T>(1.0f / s);
			return (*this) * f;
		}
	};

	// determinant algorithm
	template<std::size_t N, std::size_t M, typename T>
	T determinant_algorithm(const base_matrix<N, M, T>& m)
	{
		/* Laplace law */
		int j = 0;
		T result{};
		for (int i = 0; i < M; ++i) {
			auto minor = m.minor(i, j);
			result += std::pow(-1, i + j)*determinant_algorithm(minor);
		}
		return result;
	}

	template<typename T>
	T determinant_algorithm(const base_matrix<0, 0, T>& m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant_algorithm(const base_matrix<1, 0, T>& m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant_algorithm(const base_matrix<0, 1, T>& m)
	{
		return static_cast<T>(0.0);
	}

	template<typename T>
	T determinant_algorithm(const base_matrix<1, 1, T>& m)
	{
		return m(0, 0);
	}

	template<typename T>
	T determinant_algorithm(const base_matrix<2, 2, T>& m)
	{
		return m.data[0] * m.data[3] - (m.data[1] * m.data[2]);
	}

	template<typename T>
	T determinant_algorithm(const base_matrix<3, 3, T>& m)
	{
		// Sarrus law
		return (m.data[0] * m.data[4] * m.data[8]) -
			(m.data[1] * m.data[5] * m.data[6]) -
			(m.data[2] * m.data[3] * m.data[7]);
	}

	// undefined order zero matrix
	template<typename T>
	struct base_matrix<0, 0, T>;

	template<typename T>
	struct base_matrix<1, 0, T>;

	template<typename T>
	struct base_matrix<0, 1, T>;

	// order one matrix
	template<typename T>
	struct base_matrix1 : public base_matrix<1, 1, T>
	{
		// inherits base class constructors
		using base_matrix<1, 1, T>::base_matrix;
	};

	// order 2 matrix
	template<typename T>
	struct base_matrix2 : public base_matrix<2, 2, T>
	{
		// inherits base class constructors
		using base_matrix<2, 2, T>::base_matrix;

		static const base_matrix2<T> zero;
		static const base_matrix2<T> identity;
	};

	template<typename T> const base_matrix2<T> base_matrix2<T>::zero = base_matrix2<T>(0.0);
	template<typename T> const base_matrix2<T> base_matrix2<T>::identity = base_matrix2<T>({ 1.0, 0.0, 0.0, 1.0 });

	// order 3 matrix
	template<typename T>
	struct base_matrix3 : public base_matrix<3, 3, T>
	{
		// inherits base class constructors
		using base_matrix<3, 3, T>::base_matrix;

		static const base_matrix3<T> zero;
		static const base_matrix3<T> identity;
	};

	template<typename T> const base_matrix3<T> base_matrix3<T>::zero = base_matrix3<T>(0.0);
	template<typename T> const base_matrix3<T> base_matrix3<T>::identity = base_matrix3<T>
	(
		{ 
			1.0, 0.0, 0.0, 
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		}
	);

	// order 4 matrix
	template<typename T>
	struct base_matrix4 : public base_matrix<4, 4, T>
	{
		// inherits base class constructors
		using base_matrix<4, 4, T>::base_matrix;

		static const base_matrix4<T> zero;
		static const base_matrix4<T> identity;
	};

	template<typename T> const base_matrix4<T> base_matrix4<T>::zero = base_matrix4<T>(0.0);
	template<typename T> const base_matrix4<T> base_matrix4<T>::identity = base_matrix4<T>
	(
		{
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		}
	);

	// matrix types
	typedef base_matrix2<float> matrix2;
	typedef base_matrix3<float> matrix3;
	typedef base_matrix4<float> matrix4;
	typedef matrix2 mat2;
	typedef matrix3 mat3;
	typedef matrix4 mat4;

	typedef matrix2 fmatrix2;
	typedef matrix3 fmatrix3;
	typedef matrix4 fmatrix4;
	typedef mat2 fmat2;
	typedef mat3 fmat3;
	typedef mat4 fmat4;

	typedef base_matrix2<double> dmatrix2;
	typedef base_matrix3<double> dmatrix3;
	typedef base_matrix4<double> dmatrix4;
	typedef dmatrix2 dmat2;
	typedef dmatrix3 dmat3;
	typedef dmatrix4 dmat4;

	typedef base_matrix2<int> imatrix2;
	typedef base_matrix3<int> imatrix3;
	typedef base_matrix4<int> imatrix4;
	typedef imatrix2 imat2;
	typedef imatrix3 imat3;
	typedef imatrix4 imat4;

	typedef base_matrix2<unsigned int> umatrix2;
	typedef base_matrix3<unsigned int> umatrix3;
	typedef base_matrix4<unsigned int> umatrix4;
	typedef umatrix2 umat2;
	typedef umatrix3 umat3;
	typedef umatrix4 umat4;
};
