#include <iostream>

using namespace std;

static long long calc_pisano_period(long long m)
{
	long long previous = 0;
	long long current  = 1;

	for (long long i = 0; ; i++) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % m;

		if (previous == 0 && current == 1) {
			return i + 1;
		}
	}

	return 0;
}

static long long get_fibonacci_modulo_m(long long n, long long m)
{
	if (n <= 1) return n;

	int previous = 0;
	int current  = 1;

	for (int i = 0; i < n - 1; i++) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % m;
	}

	return current;
}

static long long get_fibonacci_huge_fast(long long n, long long m)
{
	long long pisano_period = calc_pisano_period(m);

	return get_fibonacci_modulo_m(n % pisano_period, m);
}

int main()
{
	long long n, m;
	std::cin >> n >> m;
	std::cout << get_fibonacci_huge_fast(n, m) << '\n';
}
