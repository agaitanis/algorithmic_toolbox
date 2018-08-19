#include <iostream>
#include <vector>

using namespace std;

static int max_of_int_array(int *d, int n)
{
	int	dmax = d[0];

	for (int i = 1; i < n; i++) {
		if (d[i] > dmax) dmax = d[i];
	}

	return dmax;
}

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c)
{
	int     an = (int)a.size();
	int     bn = (int)b.size();
	int     cn = (int)c.size();
	vector<vector<vector<int> > > M(an + 1, vector<vector<int> >(bn + 1, vector<int>(cn + 1, 0)));

	for (size_t k = 1; k <= cn; k++) {
		for (size_t j = 1; j <= bn; j++) {
			for (size_t i = 1; i <= an; i++) {
				int	d[7];

				d[0] = M[i-1][j][k];
				d[1] = M[i][j-1][k];
				d[2] = M[i][j][k-1];
				d[3] = M[i][j-1][k-1];
				d[4] = M[i-1][j][k-1];
				d[5] = M[i-1][j-1][k];

				if (a[i-1] == b[j-1] && a[i-1] == c[k-1]) {
					d[6] = M[i-1][j-1][k-1] + 1;
				} else {
					d[6] = M[i-1][j-1][k-1];
				}

				M[i][j][k] = max_of_int_array(d, 7);
			}
		}
	}

	return M[an][bn][cn];
}

int main()
{
	size_t an;
	cin >> an;
	vector<int> a(an);
	for (size_t i = 0; i < an; i++) {
		cin >> a[i];
	}
	size_t bn;
	cin >> bn;
	vector<int> b(bn);
	for (size_t i = 0; i < bn; i++) {
		cin >> b[i];
	}
	size_t cn;
	cin >> cn;
	vector<int> c(cn);
	for (size_t i = 0; i < cn; i++) {
		cin >> c[i];
	}
	cout << lcs3(a, b, c) << endl;
}
