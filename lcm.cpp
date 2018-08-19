#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

static int gcd_fast(int a, int b)
{
	if (b == 0) return a;

	int d = a % b;

	return gcd_fast(b, d);
}

static long long lcm_fast(int a, int b)
{
	long long gcd = gcd_fast(a, b);

	if (gcd == 0) return 0;

	return ((long long)a)*b / gcd;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
