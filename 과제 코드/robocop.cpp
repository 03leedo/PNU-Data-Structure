#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
	int N, time, count = 0, sum, diff;
	cin >> N;
	vector<pair<int, int>> points;
	vector<int> times;
	pair<int, int> point;
	for (int i = 0; i < N; i++) {
		cin >> point.first >> point.second;
		points.push_back(point);
	}
	for (int i = 0; i < 5; i++) {
		cin >> time;
		times.push_back(time);
	}
	vector<int> diffs;
	for (int i = 0; i < N; i++) {
		int next = i + 1;
		if (i == N - 1) next = 0;
		if (points[next].first - points[i].first == 0) {
			diff = points[next].second - points[i].second;
		}
		else {
			diff = points[next].first - points[i].first;
		}
		diffs.push_back(diff);
	}
	sum = accumulate(diffs.begin(), diffs.end(), 0,
		[](int sum, int diff) {return sum + abs(diff); });
	for (int& time : times) {
		count = 0;
		time %= sum;
		point = points[0];
		for (int i = 0; i < N; i++) {
			if (count + abs(diffs[i]) < time) {
				count += abs(diffs[i]);
			}
			else {
				point = points[i];
				int inc = diffs[i] / abs(diffs[i]) * (time - count);
				if (points[i + 1].first - points[i].first)
					point.first += inc;
				else point.second += inc;
				break;
			}
		}
		cout << point.first << " " << point.second << "\n";
	}
}