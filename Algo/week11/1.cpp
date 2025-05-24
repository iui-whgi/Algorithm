#include <bits/stdc++.h>
using namespace std;

struct Node {
    int   level;   // 마지막으로 고려한 아이템 인덱스 (-1: 루트)
    int   weight;  // 현재까지의 무게
    int   profit;  // 현재까지의 이익
    float bound;   // fractional-knapsack upper-bound
};

int n, W;
vector<int> w, p;     // 정렬 후 무게·이익
int maxProfit = 0;

bool ratioCmp(int i, int j) { return (float)p[i] / w[i] > (float)p[j] / w[j]; }

float calcBound(int level, int weight, int profit) {
    if (weight >= W) return 0;              // 용량 초과 → 더 탐색할 가치 없음
    float res = profit;
    int   totW = weight;
    int   j    = level + 1;

    while (j < n && totW + w[j] <= W) {
        totW += w[j];
        res  += p[j];
        ++j;
    }
    if (j < n)
        res += (W - totW) * ((float)p[j] / w[j]);

    return res;
}

void knapsackBestFirst() {
    struct Cmp { bool operator()(const Node& a, const Node& b) const
                 { return a.bound < b.bound; } };   // bound 큰 노드가 먼저
    priority_queue<Node, vector<Node>, Cmp> PQ;

    Node root{-1, 0, 0, calcBound(-1, 0, 0)};
    cout << 0 << ' ' << 0 << ' ' << 0 << ' ' << (int)root.bound << '\n';
    PQ.push(root);

    while (!PQ.empty()) {
        Node v = PQ.top(); PQ.pop();
        if (v.bound <= maxProfit || v.level == n - 1) continue; // **prune**

        for (int take = 1; take >= 0; --take) {
            Node u;
            u.level  = v.level + 1;
            u.weight = v.weight + (take ? w[u.level] : 0);
            u.profit = v.profit + (take ? p[u.level] : 0);
            u.bound  = calcBound(u.level, u.weight, u.profit);


            cout << u.level + 1 << ' ' << u.weight << ' ' << u.profit
                 << ' ' << (int)u.bound << '\n';


            if (u.weight <= W && u.profit > maxProfit)
                maxProfit = u.profit;


            if (u.bound > maxProfit)
                PQ.push(u);
        }
    }
    cout << maxProfit << '\n';
}

int main() {
    // freopen("1.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> W)) return 0;
    w.resize(n); p.resize(n);
    for (int& x : w) cin >> x;
    for (int& x : p) cin >> x;

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), ratioCmp);

    vector<int> sw(n), sp(n);
    for (int i = 0; i < n; ++i) {
        sw[i] = w[idx[i]];
        sp[i] = p[idx[i]];
    }
    w.swap(sw); p.swap(sp);

    knapsackBestFirst();
    return 0;
}
