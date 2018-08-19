#include <algorithm>
#include <iostream>
#include <vector>
#include <cfloat>
#include <cassert>
#include <climits>

using namespace std;

class ScopedClock {
	public:
		ScopedClock(const char *str) : m_t(clock()), m_str(str) {}

		~ScopedClock()
		{
			printf("%s: %f sec\n", m_str.c_str(), double(clock()-m_t)/CLOCKS_PER_SEC);
		}

	private:
		clock_t	m_t;
		string	m_str;
};

struct Point {
	Point(double x, double y) : x(x), y(y) {}

	double	x;
	double	y;
};

static bool PointCmpX(const Point &p1, const Point &p2)
{
	return p1.x < p2.x;
}

static bool PointCmpY(const Point &p1, const Point &p2)
{
	return p1.y < p2.y;
}

static double calc_dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

static double min_dist_naive(const vector<Point> &points)
{
	if (points.size() <= 1) return 0;

	double dmin = DBL_MAX;

	for (size_t i = 0; i < points.size(); i++) {
		const Point &point1 = points[i];

		for (size_t j = i+1; j < points.size(); j++) {
			const Point &point2 = points[j];
			double d = calc_dist(point1.x, point1.y, point2.x, point2.y);

			if (d < dmin) {
				dmin = d;
			}
		}
	}

	return dmin;
}

static void print_points(const char *s, const vector<Point> &points, size_t begin, size_t end)
{
	cout << s << " ";
	cout << begin << " - " << end << ": ";
	for (size_t i = begin; i < end; i++) {
		cout << "(" << points[i].x << ", " << points[i].y << ") ";
	}
	cout << endl;
}

static void print_points(const char *s, const vector<Point> &points)
{
	print_points(s, points, 0, points.size());
}

static size_t sort_by_median(vector<Point> &points, size_t begin, size_t end, int axis)
{
	size_t mid = (begin + end) / 2;

	if (axis == 1) {
		nth_element(points.begin() + begin, points.begin() + mid, points.begin() + end, PointCmpX);
	} else {
		nth_element(points.begin() + begin, points.begin() + mid, points.begin() + end, PointCmpY);
	}

	return mid;
}

static double min_dist_in_zone(const vector<Point> &points, size_t begin, size_t mid, size_t end, int axis, double xmid, double ymid, double dmin)
{
	vector<Point> points1;
	vector<Point> points2;

	if (axis == 1) {
		for (size_t i = begin; i < mid; i++) {
			const Point &point = points[i];

			if (xmid - point.x < dmin) {
				points1.push_back(point);
			}
		}

		for (size_t i = mid; i < end; i++) {
			const Point &point = points[i];

			if (point.x - xmid < dmin) {
				points2.push_back(point);
			}
		}
	} else {
		for (size_t i = begin; i < mid; i++) {
			const Point &point = points[i];

			if (ymid - point.y < dmin) {
				points1.push_back(point);
			}
		}

		for (size_t i = mid; i < end; i++) {
			const Point &point = points[i];

			if (point.y - ymid < dmin) {
				points2.push_back(point);
			}
		}
	}

	for (size_t i = 0; i < points1.size(); i++) {
		Point	&point1 = points1[i];

		for (size_t j = 0; j < points2.size(); j++) {
			Point	&point2 = points2[j];
			double	d = calc_dist(point1.x, point1.y, point2.x, point2.y);

			if (d < dmin) {
				dmin = d;
			}
		}
	}

	return dmin;
}

static int select_axis(const vector<Point> &points, size_t begin, size_t end)
{
	double	xmin = DBL_MAX;
	double	xmax = -DBL_MAX;
	double	ymin = DBL_MAX;
	double	ymax = -DBL_MAX;

	for (size_t i = begin; i < end; i++) {
		const Point &point = points[i];

		if (point.x < xmin) xmin = point.x;
		if (point.x > xmax) xmax = point.x;
		if (point.y < ymin) ymin = point.y;
		if (point.y > ymax) ymax = point.y;
	}

	if (xmax - xmin >= ymax - ymin) return 1;
	return 2;
}

static double min_dist_fast_core(vector<Point> &points, size_t begin, size_t end)
{
	if (end - begin <= 1) return DBL_MAX;

	int	axis = select_axis(points, begin, end);
	size_t	mid = sort_by_median(points, begin, end, axis);
	double	xmid = points[mid].x;
	double	ymid = points[mid].y;

	double	d1 = min_dist_fast_core(points, begin, mid);
	double	d2 = min_dist_fast_core(points, mid, end);
	double	dmin = d1 < d2 ? d1 : d2;

	dmin = min_dist_in_zone(points, begin, mid, end, axis, xmid, ymid, dmin);

	return dmin;
}

static double min_dist_fast(vector<Point> &points)
{
	ScopedClock cl(__FUNCTION__);

	if (points.size() <= 1) return 0;
	return min_dist_fast_core(points, 0, points.size());
}

static double min_dist_in_zone_new(const vector<Point> &points_y, double xmid, double dmin)
{
	for (size_t i = 0; i < points_y.size(); i++) {
		const Point &point1 = points_y[i];

		if (point1.x < xmid - dmin || point1.x > xmid + dmin) continue;

		size_t	cnt = 0;
		for (size_t j = i + 1; j < points_y.size(); j++) {
			const Point &point2 = points_y[j];

			if (point2.x < xmid - dmin || point2.x > xmid + dmin) continue;

			double	d = calc_dist(point1.x, point1.y, point2.x, point2.y);

			if (d < dmin) {
				dmin = d;
			}

			cnt++;
			if (cnt == 7) break;
		}
	}

	return dmin;
}

static double min_dist_fast_new_core(const vector<Point> &points_x, const vector<Point> &points_y)
{
	if (points_x.size() <= 3) {
		return min_dist_naive(points_x);
	}

	size_t	mid = points_x.size()/2;
	double	xmid = points_x[mid].x;
	vector<Point> points_x_1(points_x.begin(), points_x.begin() + mid);
	vector<Point> points_x_2(points_x.begin() + mid, points_x.end());
	vector<Point> points_y_1;
	vector<Point> points_y_2;

	for (size_t i = 0; i < points_y.size(); i++) {
		const Point &point = points_y[i];

		if (point.x < xmid) {
			points_y_1.push_back(point);
		} else {
			points_y_2.push_back(point);
		}
	}

	double	d1 = min_dist_fast_new_core(points_x_1, points_y_1);
	double	d2 = min_dist_fast_new_core(points_x_2, points_y_2);
	double	dmin = d1 < d2 ? d1 : d2;

	dmin = min_dist_in_zone_new(points_y, xmid, dmin);

	return dmin;
}

static double min_dist_fast_new(const vector<Point> &points)
{
	ScopedClock cl(__FUNCTION__);

	vector<Point> points_x = points;
	vector<Point> points_y = points;

	sort(points_x.begin(), points_x.end(), PointCmpX);
	sort(points_y.begin(), points_y.end(), PointCmpY);

	return min_dist_fast_new_core(points_x, points_y);
}

static void test_closest()
{
	vector<Point> points;
	int	n = rand() % 10000 + 1;

	for (int i = 0; i < n; i++) {
		int	x = rand() % 10000;
		int	y = rand() % 10000;

		points.push_back(Point(x, y));
	}

	double	dmin1 = min_dist_naive(points);
	double	dmin2 = min_dist_fast(points);
	double	dmin3 = min_dist_fast_new(points);

	if (dmin2 != dmin1 || dmin3 != dmin1) {
		printf("dmin1 = %f\n", dmin1); // alex
		printf("dmin2 = %f\n", dmin2); // alex
		printf("dmin3 = %f\n", dmin3); // alex
		assert(0);
	}
}

int main()
{
	for (int i = 0; i < 100; i++) {
		test_closest();
	}

	/*
	size_t n;
	cin >> n;
	vector<Point> points;

	for (size_t i = 0; i < n; i++) {
		int	x, y;

		cin >> x;
		cin >> y;

		points.push_back(Point(x, y));
	}

	cout.precision(10);
	cout << min_dist_fast_new(points) << endl;
	*/
}
