
#include <iostream>
#include <vector>  
#include <algorithm>
#include <string>

using namespace std;

typedef vector<vector<int>> matrix;

int minimum(int i , int j , int &k, vector<int>& d, matrix& M){
    int minValue = 1000000000, value;
    for (int m = i; m < j; m++){
        value = M[i][m] + M[m+1][j] + d[i-1]*d[m]*d[j];
        if(value < minValue){
            minValue = value;
            k = m;
        }
    }
    return minValue;
}

void chainedMatrix(matrix& M, matrix& P, vector<int>& d, int n){
    for (int i = 1; i < n; i++)
        M[i][i] = 0;
    for (int diagonal = 1; diagonal < n; diagonal++){
        for (int i = 1; i <= n - diagonal; i++){
            int j = i + diagonal, k = 0;
            M[i][j] = minimum(i, j, k, d, M);
            P[i][j] = k;
        }
    }
}

void printMatrix(matrix& m, int n){
    for (int i = 1; i < n; i++){
        for (int j = 1; j < n; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

void printPath(matrix& p, int s, int e){
    cout << "(";
    if(s == e){
        cout << "A" << s << ")";
        return;
    }
    int k = p[s][e];
    printPath(p, s, k);
    printPath(p, k+1, e);
    cout << ")";
}

int main(){
    int n;
    cin >> n;

    vector<int> a(n+1); // n+1개 필요

    for(int i=0; i<=n; i++){
        cin >> a[i];
    }

    matrix M(n+1, vector<int>(n+1, 0));
    matrix P(n+1, vector<int>(n+1, 0));

    chainedMatrix(M, P, a, n+1); // n+1 전달

    cout << "Minimum multiplication cost: " << M[1][n] << endl;
    cout << "Optimal parenthesization: ";
    printPath(P, 1, n);
    cout << endl;

    return 0;
}
