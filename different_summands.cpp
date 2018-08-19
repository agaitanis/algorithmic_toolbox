#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n)
{
	vector<int> summands;
	int	a = 0;

	while (n > 0) {
		int 	next_a = a + 2;
		int	next_n = n - (a + 1);

		if (next_a > next_n) {
			a = n;
		} else {
			a = a + 1;
		}
		summands.push_back(a);
		n -= a;
	}

	return summands;
}

int main()
{
	int n;
	cin >> n;
	vector<int> summands = optimal_summands(n);
	cout << summands.size() << '\n';
	for (size_t i = 0; i < summands.size(); ++i) {
		cout << summands[i] << ' ';
	}
}
