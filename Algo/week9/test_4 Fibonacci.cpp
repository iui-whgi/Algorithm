#include <iostream>
#include <vector>
using namespace std;

const int MOD = 10007;

int main() {
    int n;
    cin >> n; // 원하는 계단 수 입력

    vector<int> F(n + 1, 0); // 0부터 n까지 쓰니까 크기 n+1
    F[0] = 1;
    if (n >= 1) F[1] = 1;
    if (n >= 2) F[2] = 2;

    for (int i = 3; i <= n; ++i) {
        F[i] = (F[i - 1] + F[i - 2] + F[i - 3]) % MOD;
    }

    cout << F[n] << endl; // n번째 결과 출력
    return 0;
}
