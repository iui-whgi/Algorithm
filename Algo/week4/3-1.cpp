#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int MOD = 10007;

// 행렬 곱셈을 이용한 피보나치 계산
// [[1, 1], [1, 0]]^n = [[F(n+1), F(n)], [F(n), F(n-1)]]
vector<vector<int>> matrixMultiply(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    vector<vector<int>> result(2, vector<int>(2, 0));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result[i][j] = (result[i][j] + (1LL * a[i][k] * b[k][j]) % MOD) % MOD;
            }
        }
    }
    return result;
}

// 행렬 거듭제곱을 분할 정복으로 계산
vector<vector<int>> matrixPower(vector<vector<int>> matrix, long long n) {
    vector<vector<int>> result = {{1, 0}, {0, 1}}; // 단위 행렬
    
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, matrix);
        }
        matrix = matrixMultiply(matrix, matrix);
        n /= 2;
    }
    
    return result;
}

int fibonacci(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    // 피보나치 행렬 [[1, 1], [1, 0]]
    vector<vector<int>> fibMatrix = {{1, 1}, {1, 0}};
    
    // 행렬 거듭제곱 계산
    vector<vector<int>> resultMatrix = matrixPower(fibMatrix, n - 1);
    
    // F(n) = resultMatrix[0][0] * F(1) + resultMatrix[0][1] * F(0)
    // F(1) = 1, F(0) = 0
    return resultMatrix[0][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n;
    cin >> n;
    
    cout << fibonacci(n) << endl;
    
    return 0;
}