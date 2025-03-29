#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef vector<vector<int>> Matrix;

int n = 1;
int cnt = 0;

void mmult(int n, const Matrix& A, const Matrix& B, Matrix& C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

Matrix add(int n, const Matrix& A, const Matrix& B) {
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

Matrix subtract(int n, const Matrix& A, const Matrix& B) {
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void partition(int n, const Matrix& A, Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22) {
    int m = n / 2;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j+m];
            a21[i][j] = A[i+m][j];
            a22[i][j] = A[i+m][j+m];
        }
    }
}

void combine(int n, Matrix& C, const Matrix& c11, const Matrix& c12, const Matrix& c21, const Matrix& c22) {
    int m = n / 2;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = c11[i][j];
            C[i][j+m] = c12[i][j];
            C[i+m][j] = c21[i][j];
            C[i+m][j+m] = c22[i][j];
        }
    }
}

Matrix padMatrix(const Matrix& A, int originalSize, int newSize) {
    Matrix padded(newSize, vector<int>(newSize, 0));
    
    for (int i = 0; i < originalSize; i++) {
        for (int j = 0; j < originalSize; j++) {
            padded[i][j] = A[i][j];
        }
    }
    
    return padded;
}

// ! 나 이거 몰랐다.
int nextPowerOfTwo(int n) { 
    return pow(2, ceil(log2(n)));
}

void strassenAlgorithm(int n, const Matrix& A, const Matrix& B, Matrix& C) {
    cnt++;
    
    if (n <= n) {
        mmult(n, A, B, C);
        return;
    }
    
    int m = n / 2;
    
    Matrix A11(m, vector<int>(m));
    Matrix A12(m, vector<int>(m));
    Matrix A21(m, vector<int>(m));
    Matrix A22(m, vector<int>(m));
    Matrix B11(m, vector<int>(m));
    Matrix B12(m, vector<int>(m));
    Matrix B21(m, vector<int>(m));
    Matrix B22(m, vector<int>(m));
    Matrix C11(m, vector<int>(m));
    Matrix C12(m, vector<int>(m));
    Matrix C21(m, vector<int>(m));
    Matrix C22(m, vector<int>(m));
    
    partition(n, A, A11, A12, A21, A22);
    partition(n, B, B11, B12, B21, B22);
    
    Matrix M1(m, vector<int>(m));
    Matrix M2(m, vector<int>(m));
    Matrix M3(m, vector<int>(m));
    Matrix M4(m, vector<int>(m));
    Matrix M5(m, vector<int>(m));
    Matrix M6(m, vector<int>(m));
    Matrix M7(m, vector<int>(m));
    
    Matrix temp1 = add(m, A11, A22);
    Matrix temp2 = add(m, B11, B22);
    strassenAlgorithm(m, temp1, temp2, M1);
    
    temp1 = add(m, A21, A22);
    strassenAlgorithm(m, temp1, B11, M2);
    
    temp1 = subtract(m, B12, B22);
    strassenAlgorithm(m, A11, temp1, M3);
    
    temp1 = subtract(m, B21, B11);
    strassenAlgorithm(m, A22, temp1, M4);
    
    temp1 = add(m, A11, A12);
    strassenAlgorithm(m, temp1, B22, M5);
    
    temp1 = subtract(m, A21, A11);
    temp2 = add(m, B11, B12);
    strassenAlgorithm(m, temp1, temp2, M6);
    
    temp1 = subtract(m, A12, A22);
    temp2 = add(m, B21, B22);
    strassenAlgorithm(m, temp1, temp2, M7);
    
    temp1 = add(m, M1, M4);
    temp2 = subtract(m, temp1, M5);
    C11 = add(m, temp2, M7);
    
    C12 = add(m, M3, M5);
    
    C21 = add(m, M2, M4);
    
    temp1 = subtract(m, M1, M2);
    temp2 = add(m, temp1, M3);
    C22 = add(m, temp2, M6);
    
    combine(n, C, C11, C12, C21, C22);
}

void strassen(int originalSize, Matrix A, Matrix B, Matrix& C) {
    int paddedSize = nextPowerOfTwo(originalSize);
    
    if (paddedSize != originalSize) {
        Matrix paddedA = padMatrix(A, originalSize, paddedSize);
        Matrix paddedB = padMatrix(B, originalSize, paddedSize);
        Matrix paddedC(paddedSize, vector<int>(paddedSize, 0));
        
        strassenAlgorithm(paddedSize, paddedA, paddedB, paddedC);
        
        C.resize(originalSize);
        for (int i = 0; i < originalSize; i++) {
            C[i].resize(originalSize);
            for (int j = 0; j < originalSize; j++) {
                C[i][j] = paddedC[i][j];
            }
        }
    } else {
        strassenAlgorithm(originalSize, A, B, C);
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    
    n = k;
    
    Matrix A(n, vector<int>(n));
    Matrix B(n, vector<int>(n));
    Matrix C(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> B[i][j];
        }
    }
    
    strassen(n, A, B, C);
    
    cout << cnt << endl;
    
    for (int i = 0; i < n; i++) {
        cout << C[i][0];
        for (int j = 1; j < n; j++) {
            cout  << " " << C[i][j];
        }
        cout << endl;
    }
    
    return 0;
}