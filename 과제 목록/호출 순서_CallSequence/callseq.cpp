#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cctype>
#include <sstream>
#include <unordered_set>
using namespace std;
unordered_map<string, vector<string>> Functions;
vector<string> callStack;
unordered_set<string> calling;
int N, k1, k2;
bool isRecursion = false;
void execution(string F) {
	for(int i = 0; i<Functions[F].size(); i++) {
		if (isRecursion) return;
		if (Functions[F][i] == "$") {
			calling.erase(F);
			return;
		}
		if (isupper(Functions[F][i][0])) {
			if (calling.find(Functions[F][i]) != calling.end()) {
				isRecursion = true;
				return;
			}
			else {
				calling.insert(Functions[F][i]);
				execution(Functions[F][i]);
				continue;
			}
		}
		callStack.push_back(F + "-" + Functions[F][i]);
	}
}
void printCallStack(int k) {
	if (k <= (int)callStack.size()) {
		if (k > 0)
			cout << callStack[k - 1] << "\n";
		else if(k == 0)
			cout << "NONE\n";
		else {
			if (callStack.size() + k >= 0)
				cout << callStack[callStack.size() + k] << "\n";
			else cout << "NONE\n";
		}
	}
	else cout << "NONE\n";
}
int main() {
	cin >> N >> k1 >> k2;
	string temp;
	getline(cin, temp);
	while(N--){
		string line;
		getline(cin, line);
		stringstream ss(line);
		string word;
		ss >> word;
		string F = word;
		while(ss >> word){
			Functions[F].push_back(word);
		}
	}
	execution("M");
	if(isRecursion) {
		cout << "DEADLOCK";
		return 0;
	}
	printCallStack(k1);
	printCallStack(k2);
}