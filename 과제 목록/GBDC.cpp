#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main() {
	string input;
	map<set<int>, vector<int>> GBDC;
	while(getline(cin, input)){
		set<int> nums;
		stringstream ss(input);
		char command;
		int num;
		ss >> command;
		if (command == '$') return 0;
		while (ss >> num && num > 0)
			nums.insert(num);
		if (command == 'R')
			GBDC[nums].push_back(num);
		else if (command == 'Q') {
			if(GBDC.find(nums) == GBDC.end()) {
				cout << "None" << endl;
				continue;
			}
			sort(GBDC[nums].begin(), GBDC[nums].end(), greater<int>());
			for (int n : GBDC[nums])
				cout << n << " ";
			cout << endl;
		}
	}
}