#include <iostream>
#include <vector>  
#include <algorithm>
#include <string>

using namespace std;

typedef vector<vector<int>> matrix;

int minimum(int i , int j , int &k, vector<int>& d, matrix M){

    int minValue = 1000, value;

    for (int m = i; m < j-1; m++)
    {
        value = M[i][m] + M[m+1][j] + d[i-1]*d[k]*d[j];
        if(value < minValue){
            minValue = value;
            k = m;
        }
        
    }
    return minValue;
}





void chainedMatrix(matrix M,matrix P,vector<int>& d,int n){
    
    for (int i = 1; i <= n; i++)
    {
        M[i][i] = 0;
    }
    for (int digonal = 1; digonal < n-1; digonal++)
    {
        for (int i = 1; i < n - digonal; i++)
        {
            int j =  digonal + i , k ;
            M[i][j] = minimum(i,j,k,d,M);
            P[i][j] = k;
        }
        
    }
    
    

}
    
void printMatirx(matrix& m,int n){
    for (int i = 0; i < n; i++)
    {
        cout << m[i][0];
        for (int j = 1; j < n-i; j++)
        {
            cout << " " << m[i][j];

        }
        cout << endl;   
    }
}

void printPath(matrix& p,int s, int e){
    cout << "(";
    if( s == e){
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

    vector<int> a(n);

    

    matrix M(n+1, vector<int>(n+1, 0));
    matrix P(n+1, vector<int>(n+1, 0));

    for(int i=0; i<n;i++){
        cin >> a[i];
    }
    
    chainedMatrix(M,P,a,n);
    
    printMatirx(M,n);
    printMatirx(P,n);

    cout << M[1][n] << endl;
    printPath(P, 1, n);
    

    
    


    

    
}