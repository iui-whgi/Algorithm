

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000;
typedef vector<vector<int>> Matrix;

Matrix Pow(Matrix){
    
}


int main(){
    int N,K;
    cin >> N >> K;
    
    Matrix A(N, vector<int>(N,0));

    for (int i = 0; i < N; i++) {
        for ( int j = 0 ; j <N ; j++) {
        cin >> A[i][j];
        
        }
    }
    Matrix result = Pow(A,K);



}