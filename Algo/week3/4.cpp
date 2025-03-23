#include <iostream>
#include <vector>
using namespace std;



const int MOD = 1000;
typedef vector<vector<int>> Matrix;
Matrix result;

Matrix Mult(const Matrix &A, const Matrix &B) {
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


Matrix Pow(Matrix A , int k){
    int n = A.size();
    Matrix result(n, vector<int>(n, 0));
    Matrix t(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    
    while (k > 0) {
        if (k % 2 == 1) {
            result = Mult(result, A);
        }
        A = Mult(A, A);
        k /= 2;
    }
    
    return result;
}



int main(){
    int n, k;

    cin >> n >> k;
    Matrix A(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> A[i][j];
        }
    }

    result = Pow(A,k);


    for(int i = 0; i < n; i++){
        cout << result[i][0];
        
        for(int j = 1; j < n; j++){
            cout << ' '<< result[i][j] ;
        }
        cout << '\n';
    }

    return 0;
}