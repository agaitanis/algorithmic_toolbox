#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;

struct Point {
	Point(int x, int index = 0) : x(x), index(index) {}

	bool operator<(const Point &point) const
	{
		return x < point.x;
	}

	int	x;
	int	index;
};

struct Segment {
	Segment(int start, int end) : start(start), end(end) {}

	bool operator<(const Segment &s) const
	{
		return start < s.start;
	}

	int	start;
	int	end;
};

static vector<int> fast_count_segments(const vector<int> &starts, const vector<int> &ends, const vector<int> &points_x)
{
	vector<int> temp_cnt(points_x.size());
	vector<int> cnt(points_x.size());
	vector<Point> points;
	vector<Segment> segments;

	for (size_t i = 0; i < points_x.size(); i++) {
		points.push_back(Point(points_x[i], i));
	}
	for (size_t i = 0; i < starts.size(); i++) {
		segments.push_back(Segment(starts[i], ends[i]));
	}

	sort(points.begin(), points.end());
	sort(segments.begin(), segments.end());

	vector<Point>::iterator low, up;

	low = points.begin();

	for (size_t i = 0; i < segments.size(); i++) {
		low = lower_bound(low, points.end(), Point(segments[i].start));
		up = upper_bound(low, points.end(), Point(segments[i].end));

		size_t low_i = low - points.begin();
		size_t up_i = up - points.begin();

		for (size_t j = low_i; j < up_i; j++) {
			temp_cnt[j]++;
		}
	}

	for (size_t i = 0; i < points.size(); i++) {
		cnt[points[i].index] = temp_cnt[i];
	}

	return cnt;
}

static vector<int> naive_count_segments(const vector<int> &starts, const vector<int> &ends, const vector<int> &points)
{
	vector<int> cnt(points.size());
	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = 0; j < starts.size(); j++) {
			cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
		}
	}
	return cnt;
}

static void print_vec(const vector<int> &a)
{
	for (size_t i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

static void test_count_segments()
{
	int	s = 10;
	int	p = 10;
	vector<int> starts(s);
	vector<int> ends(s);
	vector<int> points(p);

	for (size_t i = 0; i < s; i++) {
		starts[i] = rand() % 100;
		ends[i] = starts[i] + rand() % 100;
	}

	for (size_t i = 0; i < p; i++) {
		points[i] = rand() % 100;
	}

	vector<int> cnts1 = fast_count_segments(starts, ends, points);
	vector<int> cnts2 = naive_count_segments(starts, ends, points);

	if (cnts1 != cnts2) {
		print_vec(starts);
		print_vec(ends);
		print_vec(points);
		print_vec(cnts1);
		print_vec(cnts2);
		assert(0);
	}
}

int main()
{
	/*
	for (int i = 0; i < 1000; i++) {
		test_count_segments();
	}
	*/

	int n, m;
	cin >> n >> m;
	vector<int> starts(n), ends(n);
	for (size_t i = 0; i < starts.size(); i++) {
		cin >> starts[i] >> ends[i];
	}
	vector<int> points(m);
	for (size_t i = 0; i < points.size(); i++) {
		cin >> points[i];
	}
	//use fast_count_segments
	vector<int> cnt = fast_count_segments(starts, ends, points);
	for (size_t i = 0; i < cnt.size(); i++) {
		cout << cnt[i] << ' ';
	}
}
