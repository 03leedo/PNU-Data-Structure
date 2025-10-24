#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Waitroom {
private:
	const int k;
	vector<vector<int>> room;
public:
	Waitroom(int k) :k(k) {}
	void split(vector<int>& seat, int index) {
		vector<int> p;
		for (int i = 0; i < k; i++) {
			p.push_back(seat[k]);
			seat.erase(seat.begin() + k);
		}
		room.emplace(room.begin() + index + 1, p);
	}
	void add(int n) {
		if (room.size() == 0) {
			vector<int> p;
			p.push_back(n);
			room.push_back(p);
			return;
		}
		if (room.back().back() < n) {
			room.back().push_back(n);
			if (room.back().size() == 2 * k)
				split(room.back(), room.size() - 1);
			return;
		}
		for (int i = 0; i < room.size(); i++) {
			if (room[i].back() > n) {
				for (int j = 0; j < room[i].size(); j++) {
					if (n < room[i][j]) {
						room[i].emplace(room[i].begin() + j, n);
						if (room[i].size() == 2 * k)
							split(room[i], i);
						return;
					}
				}
			}
			if (n < room[i + 1].front()) {
				room[i].push_back(n);
				if (room[i].size() == 2 * k)
					split(room[i], i);
				return;
			}
		}
	}
	void remove(int n) {
		if (room.size() == 0) return;
		for (int i = 0; i < room.size(); i++) {
			if (room[i].back() >= n) {
				for (int j = 0; j < room[i].size(); j++) {
					if (room[i][j] == n) {
						room[i].erase(room[i].begin() + j);
						if (room[i].size() == 0) room.erase(room.begin() + i);
						return;
					}
				}
			}
		}
	}
	void print() {
		for (int i = 0; i < room.size(); i++) {
			cout << room[i].front() << "\n";
		}
	}
};
int main() {
	int N, k, n;
	cin >> N >> k;
	char op;
	Waitroom w(k);
	for (int i = 0; i < N; i++) {
		cin >> op >> n;
		if (op == '+') w.add(n);
		else w.remove(n);
	}
	w.print();
}