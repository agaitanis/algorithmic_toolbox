#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>

using namespace std;

static void partition3(vector<int> &a, int l, int r, int *m1, int *m2)
{
	int x = a[l];
	int j1, j2;

	j1 = j2 = l;

	for (int i = l + 1; i <= r; i++) {
		if (a[i] < x) {
			j1++;
			j2++;
			swap(a[i], a[j2]);
			swap(a[j1], a[j2]);
		} else if (a[i] == x) {
			j2++;
			swap(a[i], a[j2]);
		}
	}

	swap(a[l], a[j1]);

	*m1 = j1;
	*m2 = j2;
}

static void randomized_quick_sort(vector<int> &a, int l, int r)
{
	if (l >= r) return;

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);

	int m1, m2;
	partition3(a, l, r, &m1, &m2);

	randomized_quick_sort(a, l, m1 - 1);
	randomized_quick_sort(a, m2 + 1, r);
}

static void test_quick_sort()
{
	for (int j = 0; j < 100; j++) {
		int n = rand() % 10 + 1;
		vector<int> a(n);
		vector<int> b(n);

		for (int i = 0; i < n; i++) {
			int	x = rand() % 10 + 1;

			a[i] = b[i] = x;
			cout << x << " ";
		}
		cout << endl;

		sort(a.begin(), a.end());
		randomized_quick_sort(b, 0, b.size() - 1);

		bool found_diff = false;
		for (int i = 0; i < n; i++) {
			cout << a[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < n; i++) {
			cout << b[i] << " ";
			if (b[i] != a[i]) {
				found_diff = true;
			}
		}
		cout << endl;

		assert(!found_diff);
	}
}

int main()
{
/*	test_quick_sort();*/
	int n;
	cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		cin >> a[i];
	}
	randomized_quick_sort(a, 0, a.size() - 1);
	for (size_t i = 0; i < a.size(); ++i) {
		cout << a[i] << ' ';
	}
}
