#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int k;
vector<pair<int, int>> points;
vector<int> D;

int get_distance(pair<int, int>& a, pair<int, int>& b) {
	return abs(a.first - b.first + a.second - b.second);
}

pair<int, int> get_point(int d) {
	int i, dd, dir;
	for (i = 0; D[i] < d; i++) {}
	(i == 0) ? dd = 0 : dd = D[i - 1];
	int next = (i + 1) % k;
	pair<int, int> p = points[i];
	if (points[next].first - points[i].first) {
		dir = (points[next].first > points[i].first) ? 1 : -1;
		p.first += (d - dd) * dir;
	}
	else {
		dir = (points[next].second > points[i].second) ? 1 : -1;
		p.second += (d - dd) * dir;
	}
	return p;
}
int main() {
	int t, d = 0, i, count = 0, c1d, c2d;
	float first, cycle, time;
	pair<int, int> c1, c2;
	cin >> k;
	for (i = 0; i < k; i++) {
		cin >> c1.first >> c1.second;
		points.push_back(c1);
	}
	cin >> t;

	for (i = 0; i < k - 1; i++) {
		c1 = points[i], c2 = points[i + 1];
		d += get_distance(c2, c1);
		D.push_back(d);
	}
	c1 = points[0];
	d += get_distance(c1, c2);

	D.push_back(d);
	cycle = d / 2.0;
	c1d = t % d;
	c2d = (D[k / 2 - 2] - t) % d;
	if (c2d < 0) c2d += d;

	first = D[k / 2 - 2] / 2.0;
	if (t < first) count = 0;
	else count = 1 + (t - first) / cycle;
	if (count % 2) swap(c1d, c2d);

	c1 = get_point(c1d), c2 = get_point(c2d);
	cout << c1.first << " " << c1.second << "\n";
	cout << c2.first << " " << c2.second;
}