// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math4games/math4games.h"
#include <iostream>

using namespace std;

void log(const vector4& v) {
	cout << "x:" << v.x << " y:" << v.y << " z:" << v.z << " w:" << v.z << endl;
}

int main()
{
	vector4 v;
	log(v);
	log(-v);

	int pause = 0;
	cin >> pause;
    return 0;
}


