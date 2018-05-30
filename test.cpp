// enginedev.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>

#include "vector.h"
#include "matrix.h"
#include "common.h"
#include "debug.h"

using namespace math4games;
using namespace std;

int main()
{
	// ------------------ Vector 

	vector2 v{ 1, 2 };
	vector2 w(v);
	v.x++;
	cout << w[0] << endl;
	cout << v << endl << w << endl;
	cout << v[0] << endl;
	cout << v(0) << endl;
	
	vector2 h(v);
	vector3 t({ 1, 2, 3 });
	vector2 p(t);
	cout << t << endl;
	cout << p << endl;
	cout << t.size() << endl;

	// ------------------- Matrix
	
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

	cout << m.row(1) << endl;
	cout << m.column(0) << endl;

	// ############################################# //

	cout << "Premi un tasto per continuare..." << endl;
	int input;
	cin >> input;

    return 0;
}

