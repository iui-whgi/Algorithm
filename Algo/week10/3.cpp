#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, W;
vector<int> w, p;
vector<bool> include, bestset;
int maxProfit = 0;
vector<int> original_index;  // 정렬 전 인덱스 보관
vector<int> selection_order; // 선택된 아이템의 정렬 후 인덱스 (선택 순서 보존)

void array_copy(const vector<bool>& src, vector<bool>& dest) {
    dest = src;
}

float get_bound(int i, int profit, int weight) {
    if (weight >= W) return 0;
    float bound = profit;
    int totweight = weight;
    int j = i + 1;
    while (j < n && totweight + w[j] <= W) {
        totweight += w[j];
        bound += p[j];
        j++;
    }
    if (j < n) bound += (W - totweight) * ((float)p[j] / w[j]);
    return bound;
}

bool promising(int i, int profit, int weight) {
    return get_bound(i, profit, weight) > maxProfit;
}

void knapsack(int i, int profit, int weight) {
    float bound = get_bound(i, profit, weight);
    cout << i << " " << weight << " " << profit << " " << (int)bound << " " << maxProfit << endl;

    if (weight <= W && profit > maxProfit) {
        maxProfit = profit;
        array_copy(include, bestset);
        selection_order.clear();
        for (int j = 0; j < n; j++) {
            if (include[j]) selection_order.push_back(j);
        }
    }
    if (i == n - 1) return;

    if (promising(i, profit, weight)) {
        include[i + 1] = true;
        knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
        include[i + 1] = false;
        knapsack(i + 1, profit, weight);
    }
}

int main() {
    freopen("3.txt", "r", stdin);
    cin >> n >> W;
    w.resize(n);
    p.resize(n);
    include.resize(n);
    bestset.resize(n);
    original_index.resize(n);

    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> p[i];

    // 정렬: 단위 무게당 이익 내림차순
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return (float)p[a] / w[a] > (float)p[b] / w[b];
    });

    vector<int> w2(n), p2(n), origin(n);
    for (int i = 0; i < n; i++) {
        w2[i] = w[idx[i]];
        p2[i] = p[idx[i]];
        origin[i] = idx[i];
    }
    w = w2; p = p2; original_index = origin;

    include[0] = false;
    knapsack(0, 0, 0);

    cout << maxProfit << endl;
    for (int sorted_i : selection_order) {
        cout << w[sorted_i] << " " << p[sorted_i] << endl;
    }
    return 0;
}
