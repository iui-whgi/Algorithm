#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

/* ------------ 전역 변수 ------------ */
int n, W;                      // 아이템 수, 배낭 용량
vector<int> w, p;              // 정렬-후 무게·이익 배열
vector<bool> includeItem, bestset;
int maxprofit = 0;

/* ------------ 보조 함수 ------------ */
void printNode(int level, int weight, int profit,
               int bound, int currentMax)
{
    cout << level << ' ' << weight << ' ' << profit << ' '
         << bound << ' ' << currentMax << '\n';
}

/* fractional-knapsack 기반 bound 계산 */
int calcBound(int level, int profit, int weight)
{
    int bound = profit;
    int totW  = weight;
    int j     = level + 1;

    /* 남은 아이템을 가능한 한 통째로 담기 */
    while (j < n && totW + w[j] <= W)
    {
        totW  += w[j];
        bound += p[j];
        ++j;
    }
    /* 마지막 남은 용량을 분할해서 담기 */
    if (j < n && totW < W)
        bound += (W - totW) * p[j] / w[j];   // 정수 부분만

    return bound;
}

/* ------------ 백트래킹(분기 한정) ------------ */
void knapsack(int level, int profit, int weight, int bound)
{
    /* (1) 최적 해 갱신 – 먼저 갱신 후 print 해야 max_profit이 맞음 */
    if (weight <= W && profit > maxprofit)
    {
        maxprofit = profit;
        bestset   = includeItem;
    }

    /* (2) 노드 정보 출력 */
    printNode(level + 1, weight, profit, bound, maxprofit);

    /* (3) 종료 조건 */
    if (level == n - 1 || bound <= maxprofit) return;
    if (weight > W)                           return;   // 용량 초과 시 더 이상 자식 X

    /* (4) 왼쪽 자식 : 다음 아이템 **포함** (bound는 그대로 전달) */
    includeItem[level + 1] = true;
    knapsack(level + 1,
             profit + p[level + 1],
             weight + w[level + 1],
             bound);
    includeItem[level + 1] = false;

    /* (5) 오른쪽 자식 : 다음 아이템 **제외** (새 bound 필요) */
    int newBound = calcBound(level + 1, profit, weight);
    knapsack(level + 1, profit, weight, newBound);
}

int main()
{
    // freopen("4.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* ---- 입력 ---- */
    if (!(cin >> n >> W)) return 0;
    vector<int> origW(n), origP(n);
    for (int i = 0; i < n; ++i) cin >> origW[i];
    for (int i = 0; i < n; ++i) cin >> origP[i];

    /* ---- 단위 이익 내림차순 정렬 ---- */
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b)
    {
        return (double)origP[a] / origW[a] >
               (double)origP[b] / origW[b];
    });

    w.resize(n);  p.resize(n);
    for (int i = 0; i < n; ++i)
    {
        w[i] = origW[idx[i]];
        p[i] = origP[idx[i]];
    }

    /* ---- 백트래킹 시작 ---- */
    includeItem.assign(n, false);
    bestset.assign(n, false);

    int initialBound = calcBound(-1, 0, 0);
    knapsack(-1, 0, 0, initialBound);

    /* ---- 최적 해 출력 ---- */
    cout << maxprofit << '\n';
    for (int i = 0; i < n; ++i)
        if (bestset[i])
            cout << w[i] << ' ' << p[i] << '\n';

    return 0;
}
