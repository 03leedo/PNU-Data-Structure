#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>   
#include <cmath>
#include <iomanip>

using namespace std;
using Node = pair<double, double>;

vector<int> times;
vector<double> values;
vector<Node> segment_tree;

Node make_tree(int node, int start, int end) {
    if (start == end) return segment_tree[node] = { values[start], values[start] };
    int mid = (start + end) / 2;
    Node left_Node = make_tree(node * 2, start, mid);
    Node right_Node = make_tree(node * 2 + 1, mid + 1, end);
    segment_tree[node] = { min(left_Node.first, right_Node.first), max(left_Node.second, right_Node.second) };
    return segment_tree[node];
}

Node Search(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return { 1e18, -1e18 };
    if (left <= start && end <= right) return segment_tree[node];
    int mid = (start + end) / 2;
    Node left_Node = Search(node * 2, start, mid, left, right);
    Node right_Node = Search(node * 2 + 1, mid + 1, end, left, right);
    return { min(left_Node.first, right_Node.first), max(left_Node.second, right_Node.second) };
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream file("Pitcoin.txt");
    int N;
    file >> N;
    times.resize(N);
    values.resize(N);
    segment_tree.resize(N * 4);
    for (int i = 0; i < N; i++) {
        file >> times[i] >> values[i];
    }
    cout << fixed << setprecision(3);
    file.close();
    make_tree(1, 0, N - 1);
    int M, t_s, t_e;
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> t_s >> t_e;
        int start_index = upper_bound(times.begin(), times.end(), t_s) - times.begin()-1;
        int end_index = upper_bound(times.begin(), times.end(), t_e) - times.begin()-1;
        Node result = Search(1, 0, N - 1, start_index, end_index);
        cout << result.first << " " << result.second << "\n";
    }
}