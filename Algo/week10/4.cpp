#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> mark;
int countCircuit, countPath;

void make_graph() {
    int imov[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int jmov[] = {1, 2, 2, 1, -1, -2, -2, -1};

    graph.assign(n * m, vector<int>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int from = i * m + j;
            for (int k = 0; k < 8; ++k) {
                int ni = i + imov[k];
                int nj = j + jmov[k];
                if (0 <= ni && ni < n && 0 <= nj && nj < m) {
                    int to = ni * m + nj;
                    graph[from].push_back(to);
                }
            }
        }
    }
}

void tour_circuit(int k, int v, int s) {
    if (k == n * m && find(graph[v].begin(), graph[v].end(), s) != graph[v].end()) {
        countCircuit++;
        return;
    }

    for (int u : graph[v]) {
        if (mark[u] == 0) {
            mark[u] = k + 1;
            tour_circuit(k + 1, u, s);
            mark[u] = 0;
        }
    }
}

void tour_path(int k, int v) {
    if (k == n * m) {
        countPath++;
        return;
    }

    for (int u : graph[v]) {
        if (mark[u] == 0) {
            mark[u] = k + 1;
            tour_path(k + 1, u);
            mark[u] = 0;
        }
    }
}

int main() {
    // freopen("4.txt", "r", stdin);
    cin >> n >> m;

    make_graph();

    // 회로 수 세기 (시작점 고정)
    int start = 0;
    mark.assign(n * m, 0);
    mark[start] = 1;
    countCircuit = 0;
    tour_circuit(1, start, start);
    cout << countCircuit << '\n';

    // 테스트케이스 경로 수 세기
    int T;
    cin >> T;
    while (T--) {
        int si, sj;
        cin >> si >> sj;
        int s = si * m + sj;

        mark.assign(n * m, 0);
        mark[s] = 1;
        countPath = 0;
        tour_path(1, s);
        cout << countPath << '\n';
    }

    return 0;
}
