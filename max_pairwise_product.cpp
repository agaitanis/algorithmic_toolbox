#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

long long int MaxPairwiseProduct(const vector<int> &a)
{
	size_t	max_i = -1;
	size_t	max_j = -1;

	for (size_t i = 0; i < a.size(); i++) {
		if (max_i == -1 || a[i] > a[max_i]) {
			max_i = i;
		}
	}
	if (max_i == -1) return 0;

	for (size_t i = 0; i < a.size(); i++) {
		if ((max_j == -1 || a[i] > a[max_j]) && i != max_i) {
			max_j = i;
		}
	}
	if (max_j == -1) return 0;

	return ((long long int)a[max_i]) * a[max_j];
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    long long int result = MaxPairwiseProduct(numbers);
    cout << result << "\n";
    return 0;
}
