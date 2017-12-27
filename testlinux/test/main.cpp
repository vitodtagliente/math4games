#include <iostream>
#include <chrono>
#include <math4games/math4games.h>

using namespace math4games;
using namespace std;

template<size_t n, class T>
void log(const vector<n, T>& v) {
	cout << "Vector: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	cout << endl;
}

template<size_t n, size_t m, class T>
void log(const matrix<n, m, T>& matrix) {
	cout << "Matrix " << matrix.rows << "x" << matrix.columns << ": " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << matrix(j, i) << " ";
		cout << endl;
	}
	cout << endl;
}

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
	
	vector2 v;
	v.data[0] = 1;
	v.y = 5;
	log(v);

	log(v * 2);
	log(2.f * v);
	
	vector2 w(8, 3);
	log(w);
	log(vector2(2));
	log(vector2{ {4,5} });
	cout << "up" << endl;
	log(vector2::up);
	log(vector2::up + vec2::right);
	cout << vector2::distance(vec2::up, vec2::right) << endl;

	cout << endl << endl << "#### MATRIX ####" << endl << endl;

	matrix2 m;
	log(m);
	m(1, 0) = 9;
	log(m);
	matrix2 n{ {0,1,0,1} };
	log(n);
	log(n + m);
	log(n * 2);

	timer.stop();
	cout << endl << "execution time: " << timer << " secs" << '\n';

	int input;
	cin >> input;
    return 0;
}
