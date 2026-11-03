#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using i128 = __int128_t;

struct Point {
	ll x, y;
	int id;
	Point(ll x = 0, ll y = 0, int id = 0) : x(x), y(y), id(id) {}

	bool operator<(const Point& other) const {
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

i128 cross(const Point& a, const Point& b, const Point& c) {
	return (i128)(b.x - a.x) * (c.y - a.y) - (i128)(b.y - a.y) * (c.x - a.x);
}

vector<Point> get_convex_hull(vector<Point>& pts) {
	int n = pts.size();
	if (n < 3) return {};

	sort(pts.begin(), pts.end());

	vector<Point> hull;
	for (int i = 0; i < n; ++i) {
		while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0) {
			hull.pop_back();
		}
		hull.push_back(pts[i]);
	}
	int lower_size = hull.size();
	for (int i = n - 2; i >= 0; --i) {
		while (hull.size() > lower_size && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0) {
			hull.pop_back();
		}
		hull.push_back(pts[i]);
	}
	hull.pop_back();
	return hull;
}

bool is_strictly_inside(const vector<Point>& hull, const Point& p) {
	int k = hull.size();
	if (k < 3) return false;

	if (cross(hull[0], hull[1], p) <= 0) return false;
	if (cross(hull[0], hull[k - 1], p) >= 0) return false;

	int l = 1, r = k - 2, best = 1;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (cross(hull[0], hull[mid], p) > 0) {
			best = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}

	return cross(hull[best], hull[best + 1], p) > 0;
}
bool is_strictly_inside_triangle(const Point& a, const Point& b, const Point& c, const Point& p) {
    i128 cp1 = cross(a, b, p);
    i128 cp2 = cross(b, c, p);
    i128 cp3 = cross(c, a, p);

    bool all_pos = (cp1 > 0 && cp2 > 0 && cp3 > 0);
    bool all_neg = (cp1 < 0 && cp2 < 0 && cp3 < 0);

    return all_pos || all_neg;
}

bool on_segment(const Point& a, const Point& b, const Point& p) {
    return cross(a, b, p) == 0 &&
           min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool is_inside_triangle_non_strict(const Point& a, const Point& b, const Point& c, const Point& p) {
    i128 cp1 = cross(a, b, p);
    i128 cp2 = cross(b, c, p);
    i128 cp3 = cross(c, a, p);
    bool all_non_neg = (cp1 >= 0 && cp2 >= 0 && cp3 >= 0);
    bool all_non_pos = (cp1 <= 0 && cp2 <= 0 && cp3 <= 0);
    if (cross(a, b, c) == 0) {
        return on_segment(a, b, p) || on_segment(b, c, p) || on_segment(c, a, p);
    }
    return all_non_neg || all_non_pos;
}

void solve() {
	int n, q; cin >> n >> q;

	vector<Point> pts(n);
	for (int i = 0; i < n; ++i) {
		cin >> pts[i].x >> pts[i].y;
		pts[i].id = i + 1;
	}
	vector<Point> hull = get_convex_hull(pts);
	for (int i = 0; i < q; ++i) {
		Point p;
		cin >> p.x >> p.y;
		if (is_strictly_inside(hull, p)) {
			cout << 3 << "\n";
			
		} else {
			cout << -1 << "\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	if (cin >> T) {
		while (T--) {
			solve();
		}
	}
	return 0;
}