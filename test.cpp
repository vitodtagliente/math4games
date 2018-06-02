// enginedev.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>

#include "include/math4games/math4games.h"

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
	matrix3 l(m);
	cout << l << endl;

	matrix3 A({
		-1, 2, 5,
		3, 4, 6,
		-8, 2, 12
	});

	matrix3 B({
		-2, 2, 1,
		5, 7, 4,
		-1, 4, 2
	});

	cout << A * B << endl;
	cout << A * B.column(0) << endl;

	// ------------------- Transformation

	cout << translate<4>(vector3({ 1, 2, 3 })) << endl;
	cout << rotate_z<3, float>(90) << endl;
	
	cout << pi << endl;
	cout << deg2rad(180) << endl;
	cout << 2 * pi << endl;
	cout << deg2rad(360) << endl;
	cout << pi / 4 << endl;
	cout << deg2rad(45) << endl;
	cout << 0 << endl;
	cout << deg2rad(0) << endl;

	cout << std::sin(pi/2) << " - " << std::sin(deg2rad(90)) << endl;
	cout << std::cos(pi/2) << " - " << std::cos(deg2rad(90)) << endl;

	auto position = vector2({ 1, 2 });
	auto rotation = vector2({ 45, 0 });
	auto scale = vector2({1.2f, 3.0f});
	auto obj = transform<2, float>(position, rotation, scale);

	cout << obj << endl;
	
	// ############################################# //

	cout << "Premi un tasto per continuare..." << endl;
	int input;
	cin >> input;

    return 0;
}

