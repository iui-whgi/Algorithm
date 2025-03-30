#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
const int MOD = 10007;

typedef vector<vector<int>> Matrix;


void Mmult(Matrix A, Matrix B, Matrix &r){
    
    r[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
    r[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
    
}

# 이게 내가 풀던 오리지날

int fibo(int n){
    Matrix start(2 , vector<int>(1,0));
    start[0][0] = 1;

    Matrix A(2 , vector<int>(2,1));
    Matrix r(2 , vector<int>(1,0));
    A[0][1] = 0;

    if(n==1){
        return 1;
    }
    
    for(int i=0;i<n;i++){
        Mmult(A, start, r);
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