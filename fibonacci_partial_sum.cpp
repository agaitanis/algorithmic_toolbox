#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

static long long get_fibonacci_partial_sum_naive(long long from, long long to)
{
	if (to <= 1) return to;

	long long previous = 0;
	long long current  = 1;

	for (long long i = 0; i < from - 1; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	long long sum = current;
	
	if (from == 0) from = 1;

	for (long long i = 0; i < to - from; ++i) {
		long long tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		sum += current;
	}

	return sum % 10;
}

static long long get_fibonacci_partial_sum_fast(long long from, long long to)
{
	long long previous, current, tmp_previous, sum = 0;
	const long long pisano_period = 60;
	long long pisano_periods = (to - from) / pisano_period;

	if (pisano_periods) {
		previous = 0;
		current = 1;
		sum += 1;
		for (long long i = 2; i <= 60; i++) {
			tmp_previous = previous;
			previous = current;
			current = tmp_previous + current;
			sum += current;
		}
	}

	from = from % pisano_period;
	to = to % pisano_period;

	previous = 0;
	current = 1;
	if (to > 0) sum += 1;
	for (long long i = 2; i <= to; i++) {
		tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		sum += current;
	}

	previous = 0;
	current = 1;
	if (from > 1) sum -= 1;
	for (long long i = 2; i < from; i++) {
		tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
		sum -= current;
	}

	return sum % 10;
}

static void test_fibonacci_partial_sum()
{
	for (int i = 0; i < 100; i++) {
		long long from = rand() % 60;
		long long to = rand() % 60;

		if (from > to) swap(from, to);

		long long s1 = get_fibonacci_partial_sum_naive(from, to);
		long long s2 = get_fibonacci_partial_sum_fast(from, to);

		if (s1 != s2) {
			cout << "from = " << from << ", to = " << to << endl;
			cout << "s1 = " << s1 << endl;
			cout << "s2 = " << s2 << endl;
			assert(0);
			return;
		}
	}
}

int main()
{
/*	test_fibonacci_partial_sum();*/
	long long from, to;
	cin >> from >> to;
/*	cout << get_fibonacci_partial_sum_naive(from, to) << '\n';*/
	cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
