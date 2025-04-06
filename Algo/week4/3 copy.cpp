#include <iostream>
#include <vector>

using namespace std;
const int MOD = 10007;

typedef vector<vector<int>> Matrix;

Matrix matrixMultiply(const Matrix& A, const Matrix& B) {
    Matrix result(2, vector<int>(2, 0));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
    return result;
}

Matrix matrixPower(Matrix base, int exp) {
    Matrix result = {{1, 0}, {0, 1}}; 
    while (exp > 0) {
        if (exp % 2 == 1) result = matrixMultiply(result, base);
        base = matrixMultiply(base, base);
        exp /= 2;
    }
    return result;
}


// 피보나치 수 계산
int fibo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    Matrix A = {{1, 1}, {1, 0}};
    Matrix result = matrixPower(A, n - 1);
    return result[0][0];
}

int main() {
    int n;
    cin >> n;
    cout << fibo(n) << endl;
    return 0;
}
