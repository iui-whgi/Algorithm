#include <iostream>
#include <vector>
using namespace std;

int N, M, T;
vector<pair<int, int>> testCases;

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isInside(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

int total_paths = 0;
int total_circuits = 0;

void dfs(int x, int y, int cnt, vector<vector<bool>>& visited, int sx, int sy) {
    if (cnt == N * M) {
        total_paths++;
        for (int d = 0; d < 8; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx == sx && ny == sy) {
                total_circuits++;
                break;
            }
        }
        return;
    }

    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (isInside(nx, ny) && !visited[nx][ny]) {
            visited[nx][ny] = true;
            dfs(nx, ny, cnt + 1, visited, sx, sy);
            visited[nx][ny] = false;
        }
    }
}

int count_paths(int sx, int sy) {
    total_paths = 0;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    visited[sx][sy] = true;
    dfs(sx, sy, 1, visited, sx, sy);
    return total_paths;
}

int count_circuits() {
    total_circuits = 0;
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    visited[0][0] = true;
    dfs(0, 0, 1, visited, 0, 0);
    return total_circuits;
}

int main() {
    freopen("4.txt", "r", stdin);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("4.txt", "r", stdin);
    cin >> N >> M;
    cin >> T;

    for (int i = 0; i < T; ++i) {
        int x, y;
        cin >> x >> y;
        testCases.push_back({x, y});
    }

    cout << count_circuits() << "\n";

    for (auto& [x, y] : testCases) {
        cout << count_paths(x, y) << "\n";
    }

    return 0;
}
