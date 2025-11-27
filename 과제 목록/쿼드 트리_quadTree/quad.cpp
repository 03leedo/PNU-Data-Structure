#include <iostream>
#include <string>

using namespace std;

string qts = "";
char img[128][128];

void imaging(int& i, int x, int y, int N){
	char cur = qts[i++];
	if (cur == '(') {
		int half = N / 2;
		imaging(i, x + half, y, half);
		imaging(i, x, y, half);
		imaging(i, x, y + half, half);
		imaging(i, x + half, y + half, half);
		i++;
	}
	else if(cur == '0' || cur == '1') {
		for (int b = y; b < y + N; b++) {
			for (int a = x; a < x + N; a++)
				img[b][a] = cur;
		}
	}
}
void quadtree(int x, int y, int N) {
	char first = img[y][x];
	bool same = true;
	for (int i = y; i < y + N; i++) {
		for (int j = x; j < x + N; j++) {
			if (img[i][j] != first) {
				same = false;
				break;
			}
		}
		if (!same) break;
	}
	if (same) qts += first;
	else {
		int half = N / 2;
		qts += '(';
		quadtree(x + half, y, half);
		quadtree(x, y, half);
		quadtree(x, y + half, half);
		quadtree(x + half, y + half, half);
		qts += ')';
	}
}

int main() {
	int N, S, i = 0;
	string type;
	cin >> N >> type;
	S = 1 << N;
	if (type == "QTS") {
		cin >> qts;
		imaging(i, 0, 0, S);
		for (int i = 0; i < S; i++) {
			for(int j = 0; j < S; j++)
				cout << img[i][j];
			cout << "\n";
		}
	}
	else {
		for (int i = 0; i < S; i++) {
			for (int j = 0; j < S; j++)
				cin >> img[i][j];
		}
		quadtree(0, 0, S);
		cout << qts;
	}

}