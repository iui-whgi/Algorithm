#include <iostream>
#include <vector>
using namespace std;

int N, M;
vector<vector<bool>> W;
vector<int> vindex;
int countCircuit = 0;

bool promising(int i) {
    if (i == N - 1 && !W[vindex[N - 1]][vindex[0]])
        return false;
    else if (i > 0 && !W[vindex[i - 1]][vindex[i]])
        return false;

    for (int j = 1; j < i; ++j) {
        if (vindex[i] == vindex[j])
            return false;
    }

    return true;
}

void hamiltonian(int i) {
    if (promising(i)) {
        if (i == N - 1) {
            countCircuit++;
        } else {
            for (int j = 2; j <= N; ++j) { // 2부터 시작 (1은 시작점 고정)
                vindex[i + 1] = j;
                hamiltonian(i + 1);
            }
        }
    }
}

int main() {
    freopen("4.txt", "r", stdin);
    cin >> N >> M;
    W.assign(N + 1, vector<bool>(N + 1, false));
    vindex.assign(N, 0);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        W[u][v] = W[v][u] = true;
    }

    vindex[0] = 1; // 시작점은 항상 1번 정점
    hamiltonian(0);

    cout << countCircuit << endl;
    return 0;
}
