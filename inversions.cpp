#include <iostream>
#include <vector>

using namespace std;

static void print_vec(const char *s, const vector<int> &a)
{
	cout << s;
	for (size_t i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

static long long merge(vector<int> &a, vector<int> &b, size_t left, size_t mid, size_t right)
{
	long long num = 0;
	size_t i = left;
	size_t j = mid;
	size_t k = left;

	while (i < mid && j < right) {
		if (a[i] <= a[j]) {
			b[k] = a[i];
			i++;
		} else {
			b[k] = a[j];
			j++;
			num += mid - i;
		}
		k++;
	}

	if (i == mid) {
		for (; j < right; j++, k++) {
			b[k] = a[j];
		}
	}

	if (j == right) {
		for (; i < mid; i++, k++) {
			b[k] = a[i];
		}
	}

	for (i = left; i < right; i++) {
		a[i] = b[i];
	}

	return num;
}

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right)
{
	if (right <= left + 1) return 0;

	long long num = 0;
	size_t mid = left + (right - left) / 2;

	num += get_number_of_inversions(a, b, left, mid);
	num += get_number_of_inversions(a, b, mid, right);

	num += merge(a, b, left, mid, right);

	return num;
}

int main()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		cin >> a[i];
	}
	vector<int> b(a.size());
	cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
}
