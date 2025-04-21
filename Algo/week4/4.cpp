
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


typedef vector<vector<int>> Matrix;


void Encode(Matrix A, int n){



    Matrix A11(n/2, vector<int>(n/2,0)), A12(n/2, vector<int>(n/2,0)), A21(n/2, vector<int>(n/2,0)), A22(n/2, vector<int>(n/2,0));


    int temp = A[0][0];
    bool flag = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
           if(A[i][j] != temp){
                flag = false;


            }
        }
    }
    if(flag == true){
        cout << (temp == 1 ? "b" : "w");



    }
    else{
        cout << "x";
        
        for(int i = 0; i < n/2; i++){
            for(int j = 0; j < n/2; j++){
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j+n/2];
                A21[i][j] = A[i+n/2][j];
                A22[i][j] = A[i+n/2][j+n/2];
            }
        }
        
        Encode(A11, n/2);
        Encode(A12, n/2);
        Encode(A21, n/2);
        Encode(A22, n/2);
    }
    
    
}


int main(){
    
    int n;
    
    cin >> n;

    Matrix A(n, vector<int>(n , 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
        
    }


    Encode(A, n);


    return 0;

}