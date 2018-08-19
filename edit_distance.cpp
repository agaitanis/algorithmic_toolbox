#include <iostream>
#include <string>
#include <vector>

using namespace std;

int edit_distance(const string &str1, const string &str2)
{
	int	n = (int)str1.size();
	int	m = (int)str2.size();
	vector<vector<int> > D(n + 1, vector<int>(m + 1, 0));

	for (size_t i = 0; i <= n; i++) {
		D[i][0] = i;
	}

	for (size_t j = 0; j <= m; j++) {
		D[0][j] = j;
	}

	for (size_t j = 1; j <= m; j++) {
		for (size_t i = 1; i <= n; i++) {
			int	insertion = D[i][j-1] + 1;
			int	deletion = D[i-1][j] + 1;
			int	match = D[i-1][j-1];
			int	mismatch = D[i-1][j-1] + 1;
			int	d;

			if (str1[i-1] == str2[j-1]) {
				d = match;
			} else {
				d = mismatch;
			}
			if (insertion < d) d = insertion;
			if (deletion < d) d = deletion;

			D[i][j] = d;
		}
	}

	return D[n][m];
}

int main()
{
	string str1;
	string str2;
	cin >> str1 >> str2;
	cout << edit_distance(str1, str2) << endl;
	return 0;
}
