#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Line {
    int number;
	vector<int> containers;
    bool operator<(const Line& other) const {
        if(containers.size() != other.containers.size())
            return containers.size() > other.containers.size();
		return number > other.number;
	}
};

multiset<Line> yard;
int main() {
    int N, s, ton;
    cin >> N;
    for(int i = 0; i<N;i++) {
        cin >> s;
        vector<int> containers;
		while (s--)
			cin >> ton, containers.push_back(ton);
        yard.insert({ i, containers });
    }
    while (1) {
		if(yard.size() < 2) break;
		Line max, min;
		auto max_it = yard.begin(), it = max_it;
		max = *it;
		for(it; it != yard.end(); ++it) {
			if (it->containers.size() != max.containers.size()) break;
			if (it->containers.back() > max.containers.back()) max = *it, max_it = it;
		}
		min = *(--yard.end());
		if (max.containers.size() - min.containers.size() < 2) break;
        min.containers.push_back(max.containers.back());
		max.containers.pop_back();
		yard.erase(max_it);
		yard.erase(--yard.end());
		yard.insert(max);
		yard.insert(min);
    }
	vector<Line> result(yard.begin(), yard.end());
	sort(result.begin(), result.end(), [](Line& a, Line& b) {
		return a.number < b.number;
		});
	for (auto& line : result) {
		if (line.containers.empty()) {
			cout << "0\n";
			continue;
		}
		for (auto& ton : line.containers)
			cout << ton << ' ';
		cout << '\n';
	}
}
