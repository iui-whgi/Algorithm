
#include <iostream>

#include <vector>
#include <unordered_map>

const int MOD = 10007;

using namespace std;

typedef vector<vector<int>> matrix;

vector<vector<int>> mult(matrix& A, matrix& result){

    matrix C(2,vector<int>(2,0));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                // C[i][j] = (C[i][j] + (A[i][k]*result[k][j])%MOD)%MOD ; 
                C[i][j] = (C[i][j] + 1LL * A[i][k] * result[k][j] % MOD) % MOD;
            }
        }
    }
    return C;

}

void fibo(long long n){
    if(n==1){
        cout << 1;
        return ;
    }
    

    matrix A = {{1, 1}, {1, 0}};
    matrix result = {{1, 0}, {0, 1}};

    A = {{1,1},{1,0}};    

    // ! 이렇게 하면 너어무 오래걸린다~
    // for (int i = 0; i < n; i++)
    // {
    //     result = mult( A, result);
    // }

    while(n>0){
        if(n%2==1){
            // result = mult(A, result);
            result = mult(result, A);
        }
        A = mult(A,A);
        n /=2;
        
    }
    cout << result[0][0] ;
}

int main(){
    long long n;

    cin >> n;
    fibo(n-1);
}





