#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

#define INF 0xFFFF

struct Node {
    int level;
    int bound;
    vector<int> path;

    bool operator<(const Node& other) const {
        return bound > other.bound; // 최소 우선순위 큐
    }
};

int n, m;
vector<vector<int>> adj;
int minlength = INF;
vector<int> opttour;

// 방문 경로 출력 함수
void print_node(int level, int bound, const vector<int>& path) {
    cout << level << " ";
    if (bound >= INF) cout << "INF ";
    else cout << bound << " ";
    for (int city : path)
        cout << city << " ";
    cout << '\n';
}

bool isIn(int city, const vector<int>& path) {
    return find(path.begin(), path.end(), city) != path.end();
}

int remaining_vertex(const vector<int>& path) {
    for (int i = 1; i <= n; ++i) {
        if (!isIn(i, path)) return i;
    }
    return -1;
}

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

int bound(Node* u) {
    int cost = length(u->path);
    for (int i = 1; i <= n; ++i) {
        if (!isIn(i, u->path)) {
            int minEdge = INF;
            for (int j = 1; j <= n; ++j) {
                if (i != j && !isIn(j, u->path) && adj[i][j] < minEdge)
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
    print_node(v->level, v->bound, v->path);  // 로그 출력
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
                    u->path.push_back(remaining_vertex(u->path));
                    u->path.push_back(1);
                    int len = length(u->path);
                    print_node(u->level, len, u->path);  // 로그 출력
                    if (len < minlength) {
                        minlength = len;
                        opttour = u->path;
                    }
                } else {
                    u->bound = bound(u);
                    print_node(u->level, u->bound, u->path);  // 로그 출력
                    if (u->bound < minlength)
                        PQ.push(*u);
                }
            }
        }
    }
}

int main() {
    freopen("3.txt", "r", stdin);
    cin >> n >> m;
    adj.assign(n + 1, vector<int>(n + 1, INF));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
    }

    vector<int> path;
    travel2(path, minlength);

    if (minlength >= INF) cout << "INF\n";
    else cout << minlength << "\n";

    for (int v : path)
        cout << v << " ";
    cout << "\n";

    return 0;
}
