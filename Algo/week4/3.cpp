#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
const int MOD = 10007;

typedef vector<vector<int>> Matrix;


void Mmult(Matrix& A, Matrix& B, Matrix& r){
    
    r[0][0] = (A[0][0]*B[0][0] + A[0][1]*B[1][0]) % MOD;
    r[1][0] = (A[1][0]*B[0][0] + A[1][1]*B[1][0]) % MOD;

}
// void Mmult(Matrix& A, Matrix& B, Matrix& r){
    
//     int x = (A[0][0]*B[0][0] + A[0][1]*B[1][0]) % MOD;
//     int y = (A[1][0]*B[0][0] + A[1][1]*B[1][0]) % MOD;

//     B[0][0] = x;
//     B[1][0] = y;
// }
// void Mmult(const Matrix& A, const Matrix& B, Matrix& r){
//     r[0][0] = (A[0][0]*B[0][0] + A[0][1]*B[1][0]) % MOD;
//     r[0][1] = (A[1][0]*B[0][0] + A[1][1]*B[1][0]) % MOD;
// }




int fibo(int n){
    Matrix start(2 , vector<int>(1,0));
    start[0][0] = 1;

    Matrix A(2 , vector<int>(2,1));
    Matrix r(2 , vector<int>(1,0));
    A[1][1] = 0;
    
    // for(int i=0;i<2;i++){
    //     for (int j = 0; j < 2; j++)
    //     {
    //         cout << A[i][j] << " ";
    //     }
    //     cout << endl;
        
    // }


    if(n <= 1){
        return n;
    }
    
    for(int i=0; i<n; i++){
        Mmult(A, start, r);
        start = r;
    }

    return r[0][0];

}



int main(){
    
    int n;
    cin >> n;

    int result = fibo(n);
    
    cout << result << endl;
    return 0;
    


    
    
}