#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct visit {
    int y, x, dir, cost;
    bool operator>(const visit& b) const {
        return cost > b.cost;
    }
};

int graph[25][25];
int dist[25][25][4];
int N, turn_cost;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

void bfs() {
    priority_queue<visit, vector<visit>, greater<visit>> q;

    int sy = N - 1;
    int sx = 0;

    for (int i = 0; i < 4; i++) {
        int ny = sy + dy[i];
        int nx = sx + dx[i];

        if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
        if (graph[ny][nx] == 1) continue;

        dist[ny][nx][i] = 1;
        q.push({ ny, nx, i, 1 });
    }

    while (!q.empty()) {
        visit cur = q.top();
        q.pop();

        if (cur.cost > dist[cur.y][cur.x][cur.dir]) continue;

        for (int i = 0; i < 4; i++) {
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= N || graph[ny][nx]) continue;

            int next_cost = cur.cost + 1;
            if (cur.dir != i)
                next_cost += turn_cost;
            if (next_cost < dist[ny][nx][i]) {
                dist[ny][nx][i] = next_cost;
                q.push({ ny, nx, i, next_cost });
            }
        }
    }
}

int main() {
    cin >> N >> turn_cost;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
            for (int k = 0; k < 4; k++)
                dist[i][j][k] = 1e9;
        }
    }

    bfs();

    int ans = 1e9;
    for (int i = 0; i < 4; i++)
        ans = min(ans, dist[0][N - 1][i]);
    if (ans == 1e9) cout << -1;
    else cout << ans;
}