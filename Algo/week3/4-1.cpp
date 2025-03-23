#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000;
typedef vector<vector<int>> Matrix;

// 행렬 곱셈 함수 (C = A * B) % MOD
Matrix multiply(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % MOD) % MOD;
            }
        }
    }
    
    return C;
}

// 행렬 거듭제곱 함수 (A^k) % MOD (분할 정복 방식)
Matrix power(Matrix A, long long k) {
    int n = A.size();
    Matrix result(n, vector<int>(n, 0));
    
    // 단위 행렬로 초기화 (대각선 원소가 1)
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    
    // 분할 정복으로 거듭제곱 계산
    while (k > 0) {
        if (k % 2 == 1) {
            result = multiply(result, A);
        }
        A = multiply(A, A);
        k /= 2;
    }
    
    return result;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    
    Matrix A(n, vector<int>(n, 0));
    
    // 행렬 입력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    
    // 거듭제곱 계산
    Matrix result = power(A, k);
    
    // 결과 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j];
            if (j < n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}