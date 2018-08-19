#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

static bool cmp_num(const string &a1, const string &a2)
{
	string comb1 = a1 + a2;
	string comb2 = a2 + a1;

	return atoi(comb1.c_str()) > atoi(comb2.c_str());
}

static string largest_number(vector<string> a)
{
	sort(a.begin(), a.end(), cmp_num);

	string ret;

	for (size_t i = 0; i < a.size(); i++) {
		ret += a[i];
	}

	return ret;
}

int main()
{
	int n;
	cin >> n;
	vector<string> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		cin >> a[i];
	}
	cout << largest_number(a) << endl;
}
