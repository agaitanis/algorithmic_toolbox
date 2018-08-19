#include <iostream>
#include <cstdlib>
#include <cassert>

static int gcd_naive(int a, int b)
{
	int current_gcd = 1;

	for (int d = 2; d <= a && d <= b; d++) {
		if (a % d == 0 && b % d == 0) {
			if (d > current_gcd) {
				current_gcd = d;
			}
		}
	}

	return current_gcd;
}

static int gcd_fast(int a, int b)
{
	if (b == 0) return a;

	int d = a % b;

	return gcd_fast(b, d);
}

static void stress_test_gcd()
{
	for (int i = 0; i < 1000; i++) {
		int	a = rand()%1000 + 1;
		int	b = rand()%1000 + 1;
		int	gcd1 = gcd_naive(a, b);
		int	gcd2 = gcd_fast(a, b);

		printf("gcd_naive(%d, %d) = %d\n", a, b, gcd1); // alex
		printf("gcd_fast(%d, %d) = %d\n", a, b, gcd2); // alex
		printf("\n"); // alex
		assert(gcd1 == gcd2);
	}
}

int main()
{
/*	stress_test_gcd();*/

	int a, b;

	std::cin >> a >> b;
/*	std::cout << gcd_naive(a, b) << std::endl;*/
	std::cout << gcd_fast(a, b) << std::endl;

	return 0;
}
