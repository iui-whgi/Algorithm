#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

// 메모이제이션 기반 knapsack 알고리즘
int knapsack3(int n, int W, const vector<int>& w, const vector<int>& p,
              map<pair<int, int>, int>& P) {
    if (n == 0 || W <= 0) return 0;

    pair<int, int> key = {n, W};
    if (P.find(key) != P.end()) return P[key];

    int lvalue = knapsack3(n - 1, W, w, p, P);
    int rvalue = (w[n - 1] > W) ? 0 : knapsack3(n - 1, W - w[n - 1], w, p, P) + p[n - 1];

    P[key] = max(lvalue, rvalue);
    return P[key];
}

int main() {
    int N;
    // freopen("2.txt", "r", stdin);
    cin >> N;
    vector<int> w(N), p(N);
    for (int i = 0; i < N; ++i) cin >> w[i];
    for (int i = 0; i < N; ++i) cin >> p[i];

    int M;
    cin >> M;
    vector<int> Ws(M);
    for (int i = 0; i < M; ++i) cin >> Ws[i];

    // 단위 무게당 이익 기준 정렬을 위한 인덱스
    vector<int> idx(N);
    for (int i = 0; i < N; ++i) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        double r1 = (double)p[a] / w[a];
        double r2 = (double)p[b] / w[b];
        return r1 > r2;
    });

    vector<int> sorted_w(N), sorted_p(N);
    for (int i = 0; i < N; ++i) {
        sorted_w[i] = w[idx[i]];
        sorted_p[i] = p[idx[i]];
    }

    for (int k = 0; k < M; ++k) {
        int W = Ws[k];
        map<pair<int, int>, int> P;

        int maxProfit = knapsack3(N, W, sorted_w, sorted_p, P);
        cout << maxProfit << endl;

        // DP 테이블 출력
        for (const auto& entry : P) {
            int i = entry.first.first;
            int cap = entry.first.second;
            int val = entry.second;
            cout << i << " " << cap << " " << val << endl;
        }
    }

    return 0;
}


