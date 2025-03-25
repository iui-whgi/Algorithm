
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> Matrix;

int threshold = 1; // Set threshold to at least 1
int cnt = 0;

// Basic matrix multiplication for small matrices
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

// Add two matrices
Matrix add(int n, const Matrix& A, const Matrix& B) {
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Subtract matrix B from A
Matrix subtract(int n, const Matrix& A, const Matrix& B) {
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void partition(int m, const Matrix& A, Matrix& a11, Matrix& a12, Matrix& a21, Matrix& a22) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j+m];
            a21[i][j] = A[i+m][j];
            a22[i][j] = A[i+m][j+m];
        }
    }
}

void combine(int m, Matrix& C, const Matrix& c11, const Matrix& c12, const Matrix& c21, const Matrix& c22) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = c11[i][j];
            C[i][j+m] = c12[i][j];
            C[i+m][j] = c21[i][j];
            C[i+m][j+m] = c22[i][j];
        }
    }
}

void strassen(int n, Matrix A, Matrix B, Matrix& C) {
    cnt++;
    if (n <= threshold) {
        mmult(n, A, B, C); // Actually call mmult for base case
    }
    else {
        int m = n/2;

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

        partition(m, A, A11, A12, A21, A22);
        partition(m, B, B11, B12, B21, B22);
        
        Matrix M1(m, vector<int>(m));
        Matrix M2(m, vector<int>(m));
        Matrix M3(m, vector<int>(m));
        Matrix M4(m, vector<int>(m));
        Matrix M5(m, vector<int>(m));
        Matrix M6(m, vector<int>(m));
        Matrix M7(m, vector<int>(m));

        // Temporary matrices for intermediate results
        Matrix temp1(m, vector<int>(m));
        Matrix temp2(m, vector<int>(m));

        // Strassen's 7 multiplications
        // M1 = (A11 + A22) * (B11 + B22)
        temp1 = add(m, A11, A22);
        temp2 = add(m, B11, B22);
        strassen(m, temp1, temp2, M1);

        // M2 = (A21 + A22) * B11
        temp1 = add(m, A21, A22);
        strassen(m, temp1, B11, M2);

        // M3 = A11 * (B12 - B22)
        temp1 = subtract(m, B12, B22);
        strassen(m, A11, temp1, M3);

        // M4 = A22 * (B21 - B11)
        temp1 = subtract(m, B21, B11);
        strassen(m, A22, temp1, M4);

        // M5 = (A11 + A12) * B22
        temp1 = add(m, A11, A12);
        strassen(m, temp1, B22, M5);

        // M6 = (A21 - A11) * (B11 + B12)
        temp1 = subtract(m, A21, A11);
        temp2 = add(m, B11, B12);
        strassen(m, temp1, temp2, M6);

        // M7 = (A12 - A22) * (B21 + B22)
        temp1 = subtract(m, A12, A22);
        temp2 = add(m, B21, B22);
        strassen(m, temp1, temp2, M7);

        // Calculate C submatrices using Strassen's formulas
        // C11 = M1 + M4 - M5 + M7
        temp1 = add(m, M1, M4);
        temp2 = subtract(m, temp1, M5);
        C11 = add(m, temp2, M7);

        // C12 = M3 + M5
        C12 = add(m, M3, M5);

        // C21 = M2 + M4
        C21 = add(m, M2, M4);

        // C22 = M1 - M2 + M3 + M6
        temp1 = subtract(m, M1, M2);
        temp2 = add(m, temp1, M3);
        C22 = add(m, temp2, M6);

        combine(m, C, C11, C12, C21, C22);
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    
    threshold = k; // Set threshold to k
    
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
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}