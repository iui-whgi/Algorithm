#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0xFFFF

struct Node {
    int level;
    int bound;
    vector<int> path;

    // 최소 우선순위 큐: bound가 작을수록 먼저 탐색
    bool operator<(const Node& other) const {
        return bound > other.bound;
    }
};

int n, m;
vector<vector<int>> adj;
int minlength = INF;
vector<int> opttour;

// 경로에 도시 i가 있는지 확인
bool isIn(int city, const vector<int>& path) {
    return find(path.begin(), path.end(), city) != path.end();
}

// 아직 방문하지 않은 하나 남은 도시 반환
int remaining_vertex(const vector<int>& path) {
    for (int i = 1; i <= n; ++i) {
        if (!isIn(i, path)) return i;
    }
    return -1;
}

// 경로의 총 길이 계산
int length(const vector<int>& path) {
    int total = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        int u = path[i];
        int v = path[i + 1];
        if (adj[u][v] == INF) return INF;
        total += adj[u][v];
    }
    return total;
}

// bound 함수: 현재 경로 + 남은 최소 예상 비용
int bound(Node* u) {
    int cost = length(u->path);
    for (int i = 1; i <= n; ++i) {
        if (!isIn(i, u->path)) {
            int minEdge = INF;
            for (int j = 1; j <= n; ++j) {
                if (i != j && adj[i][j] < minEdge)
                    minEdge = adj[i][j];
            }
            cost += minEdge;
        }
    }
    return cost;
}

void travel2(vector<int>& opttour, int& minlength) {
    priority_queue<Node> PQ;
    Node* v = new Node();
    v->level = 0;
    v->path.push_back(1);
    v->bound = bound(v);
    PQ.push(*v);

    while (!PQ.empty()) {
        Node v = PQ.top(); PQ.pop();
        if (v.bound < minlength) {
            for (int i = 2; i <= n; ++i) {
                if (isIn(i, v.path)) continue;

                Node* u = new Node();
                u->level = v.level + 1;
                u->path = v.path;
                u->path.push_back(i);

                if (u->level == n - 2) {
                    // 마지막 2개 도시 남았을 때: 나머지 도시와 1 추가
                    u->path.push_back(remaining_vertex(u->path));
                    u->path.push_back(1);
                    int len = length(u->path);

                    // 출력 1: pruning 전에 출력
                    cout << u->level << " " << len << " ";
                    for (int city : u->path) cout << city << " ";
                    cout << "\n";

                    if (len < minlength) {
                        minlength = len;
                        opttour = u->path;
                    }
                } else {
                    u->bound = bound(u);

                    // 출력 2: pruning 전에 출력
                    cout << u->level << " " << u->bound << " ";
                    for (int city : u->path) cout << city << " ";
                    cout << "\n";

                    if (u->bound < minlength)
                        PQ.push(*u);
                }
            }
        }
    }
}

int main() {
    freopen("3.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    adj.assign(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w; // 방향 있음에 유의
    }

    vector<int> path;
    travel2(path, minlength);

    if (minlength >= INF)
        cout << "INF\n";
    else
        cout << minlength << "\n";

    for (int v : path)
        cout << v << " ";
    cout << "\n";

    return 0;
}
