#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static bool is_majority_element_linear(vector<int> &a, int left, int right, int x)
{
	int	cnt = 0;

	for (int i = left; i <= right; i++) {
		if (a[i] == x) {
			cnt++;
		}
	}

	return cnt > (right - left + 1)/2;
}

static int get_majority_element(vector<int> &a, int left, int right)
{
	if (left > right) return -1;
	if (left == right) return a[left];

	int mid = left + (right - left)/2;
	int a_l = get_majority_element(a, left, mid);
	int a_r = get_majority_element(a, mid + 1, right);

	if (a_l == a_r) return a_l;

	if (a_l != -1 && is_majority_element_linear(a, left, right, a_l)) return a_l;
	if (a_r != -1 && is_majority_element_linear(a, left, right, a_r)) return a_r;

	return -1;
}

int main()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		cin >> a[i];
	}
	cout << (get_majority_element(a, 0, a.size()-1) != -1) << '\n';
}
