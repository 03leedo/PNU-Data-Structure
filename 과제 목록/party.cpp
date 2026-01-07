#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, char>;
map<char, vector<char>> graph;
map<char, map<char, int>> d;

void dijkstra(char start) {
	for (auto data : graph)
		d[start][data.first] = 1e9;
	d[start][start] = 0;
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({ 0, start });
	while (!q.empty()) {
		int dist = q.top().first;
		char cur = q.top().second;
		q.pop();
		if (d[start][cur] < dist) continue;
		for (char next : graph[cur]) {
			if (d[start][next] > dist + 1) {
				d[start][next] = dist + 1;
				q.push({ d[start][next], next });
			}
		}
	}
}
int main() {
	int N;
	char start[3], other;
	cin >> N >> start[0] >> start[1] >> start[2];
	while (N--) {
		char cur;
		cin >> cur;
		graph[cur].clear();
		while (cin >> other && other != '$')
			graph[cur].push_back(other);
	}
	for (char s : start)
		dijkstra(s);
	int minDist = 1e9;
	char result;
	for (auto data : graph) {
		char node = data.first;
		int dist = max({ d[start[0]][node], d[start[1]][node], d[start[2]][node] });
		if (minDist > dist) {
			minDist = dist;
			result = node;
		}
	}
	if (minDist == 1e9)
		cout << "@\n" << -1;
	else
		cout << result << '\n' << minDist * 3 - 2;
}