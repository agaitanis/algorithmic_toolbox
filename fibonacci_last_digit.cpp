#include <iostream>
#include <cassert>

static int get_fibonacci_last_digit_naive(int n)
{
	if (n <= 1) return n;

	long long int previous = 0;
	long long int current  = 1;

	for (int i = 0; i < n - 1; i++) {
		long long int tmp_previous = previous;
		previous = current;
		current = tmp_previous + current;
	}

	return current % 10;
}

static int get_fibonacci_last_digit_fast(int n)
{
	if (n <= 1) return n;

	int previous = 0;
	int current  = 1;

	for (int i = 0; i < n - 1; i++) {
		int tmp_previous = previous;
		previous = current;
		current = (tmp_previous + current)%10;
	}

	return current;
}

static void test_fibonacci_last_digit(int n)
{
	int	c1 = get_fibonacci_last_digit_naive(n);
	int	c2 = get_fibonacci_last_digit_fast(n);

	if (c1 != c2) {
		printf("naive = %d\n", c1); // alex
		printf("fast = %d\n", c2); // alex
		assert(0);
	}
}

int main()
{
	int n;
	std::cin >> n;
//	test_fibonacci_last_digit(n);
	int c = get_fibonacci_last_digit_fast(n);
	std::cout << c << '\n';
}
