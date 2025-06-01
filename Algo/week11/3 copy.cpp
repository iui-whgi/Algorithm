


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;

#define INF 0xFFFF

int n, m;
vector<vector<int>> graph;

struct Node {
    int level;
    vector<int> path;
    int bound;

    bool operator>(const Node& other) const {
        return bound > other.bound;
    }
};

bool isIn(int city, const vector<int>& path) {
    return find(path.begin(), path.end(), city) != path.end();
}

int pathLength(const vector<int>& path) {
    int len = 0;
    for (int i = 0; i < path.size() - 1; ++i) {
        int u = path[i], v = path[i + 1];
        if (graph[u][v] == INF) return INF;
        len += graph[u][v];
    }
    return len;
}

int bound(const vector<int>& path) {
    int last = path.back();
    vector<bool> visited(n + 1, false);
    for (int city : path) visited[city] = true;

    int cost = pathLength(path);
    int min_last = INF;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int min_edge = INF;
            for (int j = 1; j <= n; ++j) {
                if (i != j && graph[i][j] < min_edge)
                    min_edge = graph[i][j];
            }
            cost += min_edge;
        }
    }

    // last node -> any unvisited
    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && graph[last][i] < min_last)
            min_last = graph[last][i];
    }

    if (min_last != INF) cost += min_last;

    return cost;
}

void branchAndBoundTSP() {
    int minlength = INF;
    vector<int> opttour;

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    Node root;
    root.level = 0;
    root.path.push_back(1);
    root.bound = bound(root.path);
    pq.push(root);

    cout << root.level << " " << (root.bound == INF ? "INF" : to_string(root.bound)) << " 1\n";

    while (!pq.empty()) {
        Node v = pq.top(); pq.pop();

        if (v.bound >= minlength) continue;

        for (int i = 2; i <= n; ++i) {
            if (isIn(i, v.path)) continue;

            Node u;
            u.level = v.level + 1;
            u.path = v.path;
            u.path.push_back(i);

            if (u.level == n - 2) {
                // 마지막 노드 추가 + 1로 복귀
                for (int j = 2; j <= n; ++j) {
                    if (!isIn(j, u.path)) {
                        u.path.push_back(j);
                        break;
                    }
                }
                u.path.push_back(1);
                int tour_length = pathLength(u.path);
                cout << u.level << " " << (tour_length == INF ? "INF" : to_string(tour_length)) << " ";
                for (int city : u.path) cout << city << " ";
                cout << "\n";
                if (tour_length < minlength) {
                    minlength = tour_length;
                    opttour = u.path;
                }
            } else {
                u.bound = bound(u.path);
                cout << u.level << " " << (u.bound == INF ? "INF" : to_string(u.bound)) << " ";
                for (int city : u.path) cout << city << " ";
                cout << "\n";
                if (u.bound < minlength)
                    pq.push(u);
            }
        }
    }

    cout << (minlength == INF ? "INF" : to_string(minlength)) << "\n";
    for (int city : opttour) cout << city << " ";
    cout << "\n";
}

int main() {
    freopen("3.txt", "r", stdin);
    cin >> n >> m;
    graph.assign(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        graph[u][v] = w;
    }

    branchAndBoundTSP();

    return 0;
}
