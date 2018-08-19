#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

struct Segment {
	int 	start;
	int	end;
};

static bool cmp_segments(const Segment &seg1, const Segment &seg2)
{
	if (seg1.start < seg2.start) return true;
	if (seg1.start > seg2.start) return false;

	if (seg1.end < seg2.end) return true;
	if (seg1.end > seg2.end) return false;

	return false;
}

static vector<int> optimal_points(vector<Segment> &segments)
{
	if (segments.empty()) return vector<int>();

	sort(segments.begin(), segments.end(), cmp_segments);

	vector<int> points;
	int	point;

	point = segments[0].end;

	for (size_t i = 1; i < segments.size(); i++) {
		int	start = segments[i].start;
		int	end = segments[i].end;

		if (start > point) {
			points.push_back(point);
			point = end;
		} else {
			if (end < point) {
				point = end;
			}
		}
	}

	points.push_back(point);

	return points;
}

int main()
{
	int n;
	cin >> n;
	vector<Segment> segments(n);
	for (size_t i = 0; i < segments.size(); ++i) {
		cin >> segments[i].start >> segments[i].end;
	}
	vector<int> points = optimal_points(segments);
	cout << points.size() << "\n";
	for (size_t i = 0; i < points.size(); ++i) {
		cout << points[i] << " ";
	}
}
