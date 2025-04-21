

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <cmath>

const int MOD = 1000;


using namespace std;

typedef vector<vector<int>> Matrix;



Matrix Mult(Matrix &a, Matrix& b){
    int n = a.size();

    Matrix C(n, vector<int>(n,0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] = (C[i][j] + (a[i][k]*b[k][j] % MOD) %MOD);
            }
            
        }
        
    }
    return C;
    
}

Matrix Pow(Matrix& arr, int k){

    int n  = arr.size();
    Matrix result(n, vector<int>(n,0));

    for (int i = 0; i < n; i++)
    {
        // for (int j = 0; j < n; j++)
        // {
        //     result[i][j] = 1;
        // }
        result[i][i] = 1;
    }

    
    while(k>0){
        if(k%2 == 1){
            result = Mult(result, arr);
        }
        arr = Mult(arr, arr);
        k /=2;

    }

    return result;
}


int main(){
    int n , k;

    cin >> n >> k;

    Matrix arr(n, vector<int>(n,0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    Matrix result = Pow(arr,k);
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    
}