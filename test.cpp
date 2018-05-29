#include <iostream>

#include "include/math4games/vector.h"
#include "include/math4games/matrix.h"
#include "include/math4games/common.h"
#include "include/math4games/debug.h"

using namespace math4games;
using namespace std;

template<size_t n, class T>
void log(const base_vector<n, T>& v) {
	cout << "Vector: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	cout << endl;
}

template<size_t n, size_t m, class T>
void log(const base_matrix<n, m, T>& matrix) {
	cout << "Matrix " << matrix.rows << "x" << matrix.columns << ": " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << matrix(j, i) << "  ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	// ------------------ Vector 

	vector2 v{ 1, 2 };
	vector2 w(v);
	v.x++;
	cout << v << endl << w << endl;

	// ------------------- Matrix

	log(matrix2::zero);
	log(matrix2::identity);

	matrix2 m({ 1, 2, 3, 4 });
	cout << m << endl;
	cout << m.transpose() << endl;
	cout << m(0, 0) << endl;
	cout << m(1, 1) << endl;
	cout << m(1, 0) << endl;
	cout << m(0, 1) << endl;
	cout << m.determinant() << endl;
	cout << m * 3 << endl;
	matrix3 n({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
	cout << n << endl;
	cout << n.minor(2, 2) << endl;
	cout << n.minor(2, 2).determinant() << endl;
	cout << n.adjugate() << endl;
	cout << n.determinant() << endl;

	// ############################################# //

	cout << "Premi un tasto per continuare..." << endl;
	int input;
	cin >> input;

    return 0;
}

