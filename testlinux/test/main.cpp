#include <iostream>
#include <chrono>
#include <math4games/vector2.h>

using namespace math4games;
using namespace std;

void log(const vector2& v) {
	cout << "x: " << v.x << " y: " << v.y << endl;
}
/*
void log(const matrix2& m) {
	cout << "Matrix" << endl;
	cout << m(0, 0) << " " << m(1, 0) << endl;
	cout << m(0, 1) << " " << m(1, 1) << endl;
}
*/
void log(bool expr) {
	cout << ((expr) ? "true" : "false") << endl;
}

class Timer
{
	// make things readable
	using clk = std::chrono::steady_clock;

	clk::time_point b; // begin
	clk::time_point e; // end

public:
	void clear() { b = e = clk::now(); }
	void start() { b = clk::now(); }
	void stop() { e = clk::now(); }

	friend std::ostream& operator<<(std::ostream& o, const Timer& timer)
	{
		return o << timer.secs();
	}

	// return time difference in seconds
	double secs() const
	{
		if (e <= b)
			return 0.0;
		auto d = std::chrono::duration_cast<std::chrono::microseconds>(e - b);
		return d.count() / 1000000.0;
	}
};

int main(int argc, char **argv) {

	Timer timer;
	timer.start();

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

	/*
	vector2 v(1,2);
	log(v);
	cout << v[0] << endl;
	cout << v[1] << endl;
	v[1] = 3;
	log(v);
	*/
	/*
	cout << sizeof(vector2) << endl;
	cout << sizeof(vector3) << endl;
	cout << sizeof(vector4) << endl;
	cout << sizeof(matrix2) << endl;
	cout << sizeof(matrix3) << endl;
	*/
	/*

	matrix2 m(
		0, 1,
		2, 1
	);
	matrix2 n(
		2, 2,
		1, 1
	);
	log(m);
	m(0, 0) = 9;
	log(m);
	log(m == matrix2::identity());
	log(matrix2(1, 0, 0, 1) == matrix2::identity());

	log(matrix2::identity() * vector2(2, 0));
	log(vector2(2, 0) * matrix2::identity());
	log(matrix2(0, 1, 2, 1)*matrix2(2, 0, 0, 1));

	log(m += n);
	log(m);
	cout << m.determinant() << endl;
	cout << matrix2::identity().determinant() << endl;

	matrix2 c(4, 3, 1, 1);
	log(c);
	log(c.inverse());
	log(c*c.inverse());
	cout << matrix2(1, -4, 0, 3).determinant() << endl;
	cout << matrix2(2, 1, -1, 3).determinant() << endl;

	*/

	vector2 v(8, 2);
	cout << v[0] << " " << v[1] << endl;
	v[1] = 4;
	log(v);
	v[3] = 5;
	log(v);
	log(3.f * v);
	log(v * 3);

	timer.stop();
	cout << endl << "execution time: " << timer << " secs" << '\n';

	int input;
	cin >> input;
    return 0;
}
