#include <iostream>
#include <math4games/math4games.h>

using namespace math4games;
using namespace std;

void log(const vector2& v) {
	cout << "x: " << v.x << " y: " << v.y << endl;
}

void log(const matrix2& m) {
	cout << "Matrix" << endl;
	cout << m(0, 0) << " " << m(1, 0) << endl;
	cout << m(0, 1) << " " << m(1, 1) << endl;
}

int main(int argc, char **argv) {
    
	/*
	vector2 v(1);
	log(v);
	log(-v);
	v *= 2;
	log(v);
	v += v;
	log(v);

	vector2 a(1);
	vector2 b(2);
	log(a + b);
	vector2 c = a - b;
	c.x = 9;
	log(c);
	log(a - b);
	cout << a*b << endl;
	log(a * 5);
	log(a / 2);
	log(2 * a);
	cout << a.distance(b) << endl;
	cout << vector2::distance(a, b) << endl;
	log(a.project(b));
	log(a.reject(b));

	*/

	matrix2 m(
		0, 1,
		2, 1
	);
	log(m);
	float a00 = m(0, 0);
	a00 = 9;
	log(m);

	int input;
	cin >> input;
    return 0;
}
