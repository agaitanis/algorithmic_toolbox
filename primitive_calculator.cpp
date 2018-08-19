#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> optimal_sequence_greedy(int n)
{
	vector<int> sequence;
	while (n >= 1) {
		sequence.push_back(n);
		if (n % 3 == 0) {
			n /= 3;
		} else if (n % 2 == 0) {
			n /= 2;
		} else {
			n = n - 1;
		}
	}
	reverse(sequence.begin(), sequence.end());
	return sequence;
}

vector<int> optimal_sequence_dynamic(int n)
{
	vector<int> operations(n+1);

	operations[0] = 0;

	for (int i = 1; i <= n; i++) {
		operations[i] = operations[i-1] + 1;

		if (i%2 == 0 && operations[i/2] + 1 < operations[i]) {
			operations[i] = operations[i/2] + 1;
		}
		if (i%3 == 0 && operations[i/3] + 1 < operations[i]) {
			operations[i] = operations[i/3] + 1;
		}
	}

	vector<int> sequence;

	for (int i = n; i >= 1; ) {
		sequence.push_back(i);
		if (i%2 == 0 && operations[i/2] + 1 == operations[i]) {
			i /= 2;
		} else if (i%3 == 0 && operations[i/3] + 1 == operations[i]) {
			i /= 3;
		} else {
			i--;
		}
	}

	reverse(sequence.begin(), sequence.end());

	return sequence;
}

int main()
{
	int n;
	cin >> n;
	vector<int> sequence = optimal_sequence_dynamic(n);
	cout << sequence.size() - 1 << endl;
	for (size_t i = 0; i < sequence.size(); ++i) {
		cout << sequence[i] << " ";
	}
}
