#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10007;

int main() {
    int n;
    cin >> n; // 구하고 싶은 A_n 입력

    vector<int> A(n + 1, 0);
    A[0] = 3;

    for (int k = 1; k <= n; ++k) {
        long long sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += 1LL * A[i] * A[k - 1 - i]; // long long으로 오버플로 방지
        }
        A[k] = sum % MOD;
    }

    cout << A[n] << endl; // A_n 결과 출력
    return 0;
}
