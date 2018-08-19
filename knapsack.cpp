#include <iostream>
#include <vector>

using namespace std;

static int knapsack_without_repetitions(int W, const vector<int> &weights, const vector<int> &values)
{
	int	n = (int)weights.size();
	vector<vector<int> > v(n + 1, vector<int>(W + 1, 0));

	for (size_t i = 1; i <= n; i++) {
		for (size_t w = 1; w <= W; w++) {
			int	wi = weights[i-1];
			int	vi = values[i-1];
			int	val;

			v[i][w] = v[i-1][w];
			if (wi <= w) {
				val = v[i-1][w-wi] + vi;
				if (v[i][w] < val) {
					v[i][w] = val;
				}
			}
		}
	}

	return v[n][W];
}

static int optimal_weight(int W, const vector<int> &weights)
{
	return knapsack_without_repetitions(W, weights, weights);
}

int main()
{
	int n, W;
	cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
	cout << optimal_weight(W, w) << '\n';
}
