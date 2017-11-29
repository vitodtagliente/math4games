// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math4games/math4games.h"
#include <iostream>

using namespace std;
using namespace math4games;

void log(const vector4& v) {
	cout << "x:" << v.x << " y:" << v.y << " z:" << v.z << " w:" << v.w << endl;
}

void log(const vector3& v) {
	cout << "x:" << v.x << " y:" << v.y << " z:" << v.z << endl;
}

void log(const vector2& v) {
	cout << "x:" << v.x << " y:" << v.y << endl;
}

void log(bool value)
{
	if (value)
		cout << "true" << endl;
	else cout << "false" << endl;
}

int main()
{
	/* Vectors tests */

	vector4 zero;
	vector4 v(1);
	vector4 w(2);

	log(zero);
	log(v);
	log(-v);
	log(w);

	log(v + w);
	log(v - w);
	log(v * 7);

	log(v.normalize());
	cout << v.magnitude() << endl;
	cout << v.normalize().magnitude() << endl;

	log(v == w);
	log(v == v);
	log(v != w);

	cout << v.distance(w) << endl;
	cout << vector4::distance(v, w) << endl;

	int pause = 0;
	cin >> pause;
    return 0;
}


