#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<vector<bool>> adj; // 인접행렬
vector<int> vcolor;
int totalWays = 0;

// 인접한 정점과 색이 겹치는지 확인
bool promising(int i) {
    for (int j = 1; j < i; ++j) {
        if (adj[i][j] && vcolor[i] == vcolor[j])
            return false;
    }
    return true;
}

// 백트래킹을 통한 색칠 방법 계산
void m_coloring(int i, int m) {
    if (i > N) {
        totalWays++;
        return;
    }

    for (int color = 1; color <= m; ++color) {
        vcolor[i] = color;
        if (promising(i))
            m_coloring(i + 1, m);
        vcolor[i] = 0; // backtrack
    }
}

int main() {
    // freopen("3.txt", "r", stdin);
    cin >> N >> M;
    adj.assign(N + 1, vector<bool>(N + 1, false));
    vcolor.assign(N + 1, 0);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    int minColors = 1;
    while (true) {
        totalWays = 0;
        m_coloring(1, minColors);
        if (totalWays > 0)
            break;
        minColors++;
    }

    cout << minColors << endl;
    cout << totalWays << endl;

    return 0;
}
