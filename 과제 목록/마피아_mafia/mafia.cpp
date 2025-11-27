#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;
struct Capo {
	int servant_count, depth;
	string name;
};

unordered_map<string, vector<string>> subordinate;
unordered_set<string> servants, bosses;
vector<Capo> rank_list;

int travel(string person, int cur_depth) {
	int count = 0, depth = cur_depth + 1;
	for (string servant : subordinate[person])
		count += 1 + travel(servant, depth);
	rank_list.push_back({ count, cur_depth, person });
	return count;
}
int main() {
	int N;
	string servant, boss, root;
	cin >> N;
	while (--N) {
		cin >> servant >> boss;
		servants.insert(servant);
		bosses.insert(boss);
		subordinate[boss].push_back(servant);
	}
	for (string boss : bosses)
		if (servants.find(boss) == servants.end()) {
			root = boss;
			break;
		}
	travel(root, 0);

	sort(rank_list.begin(), rank_list.end(), [&](Capo a, Capo b) {
		if (a.servant_count == b.servant_count) {
			if (a.depth == b.depth)
				return a.name < b.name;
			return a.depth < b.depth;
		}
		return a.servant_count > b.servant_count;
	});

	for (Capo capo : rank_list)
		cout << capo.name << '\n';
}