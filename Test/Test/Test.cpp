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

	

	int pause = 0;
	cin >> pause;
    return 0;
}


