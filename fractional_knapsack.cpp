#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct Item {
	Item(int _v, int _w) : v(_v), w(_w) {}

	int	v;
	int	w;
};

static bool ItemCmp(const Item &lhs, const Item &rhs)
{
	return (double)lhs.v/(double)lhs.w > (double)rhs.v/(double)rhs.w;
}

static vector<Item> build_items(const vector<int> &values, const vector<int> &weights)
{
	vector<Item> items;

	for (size_t i = 0; i < values.size(); i++) {
		items.push_back(Item(values[i], weights[i]));
	}

	sort(items.begin(), items.end(), ItemCmp);

	return items;
}

static double get_optimal_value(int capacity, vector<int> weights, vector<int> values)
{
	double value = 0.0;
	vector<Item> items = build_items(values, weights);

	for (size_t i = 0; i < items.size(); i++) {
		if (capacity <= 0) return value;

		Item &item = items[i];
		int	w = min(capacity, item.w);

		value += (double)w*(double)item.v/(double)item.w;
		capacity -= w;
	}

	return value;
}

int main()
{
	int n;
	int capacity;
	std::cin >> n >> capacity;
	vector<int> values(n);
	vector<int> weights(n);
	for (int i = 0; i < n; i++) {
		std::cin >> values[i] >> weights[i];
	}

	double optimal_value = get_optimal_value(capacity, weights, values);

	std::cout.precision(10);
	std::cout << optimal_value << std::endl;
	return 0;
}
