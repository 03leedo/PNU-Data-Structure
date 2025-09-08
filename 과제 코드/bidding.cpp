#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n, bid_price, count = 1;
	string name;
	pair<int, string> bid, max;
	cin >> n;
	vector<pair<int, string>> list;
	for (int i = 0; i < n; i++) {
		cin >> name >> bid_price;
		bid = { bid_price, name };
		list.push_back(bid);
	}
	sort(list.begin(), list.end(), [](pair<int, string> a, pair<int, string> b) {return a.first > b.first; });
	max = list[0];
	for (int i = 1; i < n; i++) {
		if (max.first == list[i].first) count++;
		else {
			if (count == 1) {
				break;
			}
			else {
				max = list[i];
				count = 1;
			}
		}
	}
	if (count > 1) cout << "NONE";
	else cout << max.second;
}