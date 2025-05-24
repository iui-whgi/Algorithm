#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int level;
    int weight;
    int profit;
    float bound;
};

int n, W;
vector<int> w, p;
int maxProfit = 0;

bool cmp(int i, int j) {
    return (float)p[i] / w[i] > (float)p[j] / w[j];
}

float bound(Node u) {
    if (u.weight >= W) return 0;
    float result = u.profit;
    int totweight = u.weight;
    int j = u.level + 1;

    while (j < n && totweight + w[j] <= W) {
        totweight += w[j];
        result += p[j];
        j++;
    }
    if (j < n)
        result += (W - totweight) * ((float)p[j] / w[j]);

    return result;
}

void knapsackBFS() {
    queue<Node> Q;
    Node u, v;
    v.level = -1;
    v.weight = 0;
    v.profit = 0;
    v.bound = bound(v);
    Q.push(v);

    while (!Q.empty()) {
        v = Q.front(); Q.pop();

        if (v.level == n - 1) continue;

        u.level = v.level + 1;

        // Case 1: include u.level item
        u.weight = v.weight + w[u.level];
        u.profit = v.profit + p[u.level];
        u.bound = bound(u);
        if (u.weight <= W && u.profit > maxProfit)
            maxProfit = u.profit;
        if (u.bound > maxProfit) {
            cout << u.level + 1 << " " << u.weight << " " << u.profit << " " << (int)u.bound << '\n';
            Q.push(u);
        }

        // Case 2: exclude u.level item
        u.weight = v.weight;
        u.profit = v.profit;
        u.bound = bound(u);
        if (u.bound > maxProfit) {
            cout << u.level + 1 << " " << u.weight << " " << u.profit << " " << (int)u.bound << '\n';
            Q.push(u);
        }
    }

    cout << maxProfit << '\n';
}

int main() {
    freopen("1.txt", "r", stdin);
    cin >> n >> W;
    w.resize(n); p.resize(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> p[i];

    // 내림차순 정렬
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), cmp);

    vector<int> tw(n), tp(n);
    for (int i = 0; i < n; i++) {
        tw[i] = w[idx[i]];
        tp[i] = p[idx[i]];
    }
    w = tw; p = tp;

    // 루트 노드도 출력
    cout << "0 0 0 " << (int)bound({-1, 0, 0, 0}) << '\n';
    knapsackBFS();
    return 0;
}
