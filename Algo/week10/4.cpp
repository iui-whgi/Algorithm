#include <iostream>
#include <vector>
using namespace std;

int N, M, T;
vector<pair<int, int>> testCases;

vector<vector<int>> graph;
vector<int> mark;

int result = 0;
bool checkCircuit = false;

int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// 좌표 → 인덱스
int toIndex(int x, int y) {
    return x * M + y;
}

// 그래프 생성
void make_graph() {
    graph.assign(N * M, vector<int>());
    for (int x = 0; x < N; ++x) {
        for (int y = 0; y < M; ++y) {
            int from = toIndex(x, y);
            for (int d = 0; d < 8; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (0 <= nx && nx < N && 0 <= ny && ny < M) {
                    int to = toIndex(nx, ny);
                    graph[from].push_back(to);
                }
            }
        }
    }
}

// 경로 탐색 (회로 or 일반 경로)
void tour(int k, int v, int s) {
    if (k == N * M) {
        if (checkCircuit) {
            for (int u : graph[v]) {
                if (u == s) {
                    result++;
                    break;
                }
            }
        } else {
            result++;
        }
        return;
    }

    for (int u : graph[v]) {
        if (mark[u] == 0) {
            mark[u] = k + 1;
            tour(k + 1, u, s);
            mark[u] = 0;
        }
    }
}

// 회로 계산
int count_circuits() {
    int start = toIndex(0, 0);
    mark.assign(N * M, 0);
    mark[start] = 1;
    result = 0;
    checkCircuit = true;
    tour(1, start, start);
    return result;
}

// 경로 계산
int count_paths(int sx, int sy) {
    int start = toIndex(sx, sy);
    mark.assign(N * M, 0);
    mark[start] = 1;
    result = 0;
    checkCircuit = false;
    tour(1, start, start);
    return result;
}

int main() {
    // freopen("4.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> T;
    testCases.resize(T);
    for (int i = 0; i < T; ++i) {
        cin >> testCases[i].first >> testCases[i].second;
    }

    make_graph();

    cout << count_circuits() << "\n";
    for (auto &[x, y] : testCases) {
        cout << count_paths(x, y) << "\n";
    }

    return 0;
}
