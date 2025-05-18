#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N;
vector<int> col;  // 1-based index
int solutionCount = 0;
string maxConcatValue = "0";

// 현재 위치가 유망한지 판단
bool promising(int i) {
    for (int k = 1; k < i; ++k) {
        if (col[i] == col[k] || abs(col[i] - col[k]) == i - k)
            return false;
    }
    return true;
}

// 백트래킹으로 모든 배치 시도
void queens(int i) {
    if (promising(i)) {
        if (i == N) {
            solutionCount++;
            string concat;
            for (int k = 1; k <= N; ++k)
                concat += to_string(col[k]);
            if (concat > maxConcatValue)
                maxConcatValue = concat;
        } else {
            for (int j = 1; j <= N; ++j) {
                col[i + 1] = j;
                queens(i + 1);
            }
        }
    }
}

int main() {
    // freopen("1.txt", "r", stdin);
    cin >> N;
    col.assign(N + 1, 0);
    queens(0);

    cout << solutionCount << endl;
    cout << maxConcatValue << endl;

    return 0;
}
