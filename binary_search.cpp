#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

static int binary_search(const vector<int> &a, int x)
{
	int	low = 0;
	int	high = (int)a.size() - 1; 

	while (low <= high) {
		int	mid = low + (high-low)/2;

		if (x < a[mid]) {
			high = mid - 1;
		} else if (x > a[mid]) {
			low = mid + 1;
		} else {
			return mid;
		}
	}

	return -1;

}

static int linear_search(const vector<int> &a, int x)
{
	for (size_t i = 0; i < a.size(); ++i) {
		if (a[i] == x) return i;
	}
	return -1;
}

static void test_binary_search()
{
	int	n = rand()%1000000 + 1;
	int	k = rand()%1000000 + 1;
	vector<int> a(n);
	vector<int> b(k);

	for (int i = 0; i < n; i++) {
		a[i] = rand()%100 + 1;
	}
	sort(a.begin(), a.end());

	for (int i = 0; i < k; i++) {
		b[i] = rand()%100 + 1;
	}

	for (int i = 0; i < k; i++) {
		int	index_b = binary_search(a, b[i]);

		if (index_b != -1) {
			assert(a[index_b] == b[i]);
		} else {
			assert(linear_search(a, b[i]) == -1);
		}
	}
}

int main()
{
/*	test_binary_search();*/
	int n;
	cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		cin >> a[i];
	}
	int m;
	cin >> m;
	vector<int> b(m);
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
	}
	for (int i = 0; i < m; ++i) {
		cout << binary_search(a, b[i]) << ' ';
	}
}
