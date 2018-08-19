#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>

using namespace std;

long long eval(long long a, long long b, char op)
{
	if (op == '*') {
		return a * b;
	} else if (op == '+') {
		return a + b;
	} else if (op == '-') {
		return a - b;
	} else {
		assert(0);
	}
}

static void min_and_max(const vector<char> &op, vector<vector<long long> > &m, vector<vector<long long> > &M, int i, int j)
{
	long long min = LLONG_MAX;
	long long max = -LLONG_MAX;

	for (int k = i; k <= j - 1; k++) {
		long long a = eval(M[i][k], M[k+1][j], op[k]);
		long long b = eval(M[i][k], m[k+1][j], op[k]);
		long long c = eval(m[i][k], M[k+1][j], op[k]);
		long long d = eval(m[i][k], m[k+1][j], op[k]);

		if (a < min) min = a;
		if (b < min) min = b;
		if (c < min) min = c;
		if (d < min) min = d;

		if (a > max) max = a;
		if (b > max) max = b;
		if (c > max) max = c;
		if (d > max) max = d;
	}

	m[i][j] = min;
	M[i][j] = max;
}

long long get_maximum_value(const string &exp)
{
	vector<int> d;
	vector<char> op;

	for (int i = 0; i < exp.size(); i++) {
		if (i % 2 == 0) {
			d.push_back(exp[i] - '0');
		} else {
			op.push_back(exp[i]);
		}
	}

	int	n = d.size();
	vector<vector<long long> > m(n, vector<long long>(n, 0));
	vector<vector<long long> > M(n, vector<long long>(n, 0));

	for (int i = 0; i < n; i++) {
		m[i][i] = d[i];
		M[i][i] = d[i];
	}

	for (int s = 1; s <= n - 1; s++) {
		for (int i = 0; i < n - s; i++) {
			min_and_max(op, m, M, i, i + s);
		}
	}

	return M[0][n - 1];
}

int main()
{
	string s;
	cin >> s;
	cout << get_maximum_value(s) << '\n';
}
