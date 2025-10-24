#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Customer {
	int id, things, t, num;
};
struct cmp {
	bool operator()(Customer a, Customer b) {
		if (a.t != b.t) return a.t > b.t;
		else return a.num < b.num;
	}
};

int main() {
	int N, k, t = 0;
	cin >> N >> k;
	priority_queue<Customer, vector<Customer>, cmp> pq;
	priority_queue<int, vector<int>, greater<int>> counter;
	vector<int> result;
	for (int i = 1; i <= k; i++)
		counter.push(i);
	while (N--) {
		Customer c;
		cin >> c.id >> c.things;
		c.t = t + c.things;
		if (pq.size() != k) {
			c.num = counter.top();
			counter.pop();
			pq.push(c);
		}
		else {
			Customer front = pq.top();
			counter.push(front.num);
			pq.pop();
			t = front.t;
			c.t = t + c.things;
			result.push_back(front.id);
			while (!pq.empty() && pq.top().t == t) {
				result.push_back(pq.top().id);
				counter.push(pq.top().num);
				pq.pop();
			}
			c.num = counter.top();
			pq.push(c);
			counter.pop();
		}
	}
	while (!pq.empty()) {
		Customer front = pq.top();
		pq.pop();
		result.push_back(front.id);
	}
	for (int id : result)
		cout << id << "\n";
}