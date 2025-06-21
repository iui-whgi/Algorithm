#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 9999;
int N, M;

using matrix_t = vector<vector<int>>;

int countSetBits(int mask) {
    int count = 0;
    while (mask) {
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

bool isIn(int i, int A) {
    return (A >> (i - 2)) & 1;
}

int remove(int A, int j) {
    return A & ~(1 << (j - 2));
}

// 최소값과 j 인덱스를 반환
pair<int, int> minimum(int n, int i, int A, const matrix_t &W, const matrix_t &D) {
    int minCost = INF;
    int minJ = -1;
    for (int j = 2; j <= n; ++j) {
        if (!isIn(j, A)) continue;
        int Aj = remove(A, j);
        int cost = W[i][j] + D[j][Aj];
        if (cost < minCost) {
            minCost = cost;
            minJ = j;
        }
    }
    return {minCost, minJ};
}

void travel(int n, matrix_t &W, matrix_t &D, matrix_t &P, int &minlength) {
    int subset_size = pow(2, n - 1);
    for (int i = 2; i <= n; i++)
        D[i][0] = W[i][1];  // 시작점에서 바로 돌아가는 거리

    for (int k = 1; k <= n - 2; k++) {
        for (int A = 0; A < subset_size; A++) {
            if (countSetBits(A) != k) continue;
            for (int i = 2; i <= n; i++) {
                if (isIn(i, A)) continue;
                auto [val, j] = minimum(n, i, A, W, D);
                D[i][A] = val;
                P[i][A] = j;
            }
        }
    }

    int A = subset_size - 1;  // V - {v1}
    auto [val, j] = minimum(n, 1, A, W, D);
    D[1][A] = val;
    P[1][A] = j;
    minlength = D[1][A];
}

void printPath(int start, int A, const matrix_t &P) {
    cout << start << " ";
    while (A != 0) {
        int j = P[start][A];
        cout << j << " ";
        A = remove(A, j);
        start = j;
    }
    cout << "1" << endl;
}

int main() {
    freopen("2.txt", "r", stdin);
    cin >> N >> M;
    matrix_t W(N + 1, vector<int>(N + 1, INF));
    matrix_t D(N + 1, vector<int>(1 << (N - 1), INF));
    matrix_t P(N + 1, vector<int>(1 << (N - 1), -1));

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        W[u][v] = w;
    }

    int minlength;
    travel(N, W, D, P, minlength);

    cout << minlength << endl;
    int full = (1 << (N - 1)) - 1;
    printPath(1, full, P);

    // D 테이블 출력
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < (1 << (N - 1)); j++) {
            if (D[i][j] != INF)
                cout << i << " " << j << " " << D[i][j] << endl;
        }
    }

    return 0;
}
