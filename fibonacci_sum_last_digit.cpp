#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

static int fibonacci_sum_naive(long long n)
{
	if (n <= 1) return n;

	int previous = 0;
	int current  = 1;
	int sum      = 1;

	for (long long i = 0; i < n - 1; ++i) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current) % 10;
		sum = (sum + current) % 10;
	}

	return sum;
}

static int fibonacci_sum_fast(long long n)
{
	if (n <= 1) return n;

	vector<int> a(2);
	vector<int> s(2);
	int	pisano_period = 0;

	a[0] = 0;
	a[1] = 1;

	s[0] = 0;
	s[1] = 1;

	for (int i = 2; i <= n; i++) {
		int	new_a = (a[i-2] + a[i-1])%10;

		a.push_back((a[i-2] + a[i-1])%10);
		s.push_back((s[i-1] + a[i])%10);

		if (a[i] == 1 && a[i-1] == 0) {
			pisano_period = i-1;
			break;
		}
	}

	if (pisano_period > 0) {
		return s[n % pisano_period];
	}

	return s[n];
}

static void test_fibonacci_sum()
{
	for (int i = 0; i < 100; i++) {
		long long n = rand() % 100000000;
		long long s1 = fibonacci_sum_naive(n);
		long long s2 = fibonacci_sum_fast(n);

		cout << "n = " << n << endl;

		if (s1 != s2) {
			cout << "s1 = " << s1 << endl;
			cout << "s2 = " << s2 << endl;
			assert(0);
			return;
		}
	}
}

int main()
{
	long long n = 0;

/*	test_fibonacci_sum();*/

	cin >> n;
	cout << fibonacci_sum_fast(n) << endl;
}
