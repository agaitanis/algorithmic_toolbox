#include <iostream>
#include <vector>

using namespace std;

int get_change(int m)
{
	vector<int> changes = {10, 5, 1};
	int	i = 0, n = 0;

	while (m > 0) {
		while (i < changes.size() && m >= changes[i]) {
			m -= changes[i];
			n++;
		}
		i++;
	}

	return n;
}

int main()
{
	int	m;

	cin >> m;
	cout << get_change(m) << '\n';
}
