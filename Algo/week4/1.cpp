

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<vector<int>> Matrix;




int main(){
    int n , k;
    cin >> n >> k;
    
    Matrix A(n, vector<int>(n));
    Matrix B(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> B[i][j];
        }
    }


    

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << A[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << B[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    
    
}