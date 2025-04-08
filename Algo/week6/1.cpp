//? 5.1
#include <iostream>
#include <vector>  
#include <algorithm>
#include <string>

using namespace std;

typedef vector<vector<int>> matrix;

#define INF 999999


void chainedMatrix(matrix& M,matrix& P,vector<int>& D,int n){
    
    for (int i = 0; i <= n; i++)
    {
        M[i][i] = P[i][i] =0;
    }
    

    for(int gap = 1; gap < n; gap++){
        
        for (int i = 1; i <= n - gap; i++)
        {
            int j = i + gap;
            for(int k=i ; k<j;k++)
            if(M[i][j] > M[i][k] + M[k+1][j] + D[i-1]*D[k]*D[j]){
                M[i][j] = M[i][k] + M[k+1][j] + D[i-1]*D[k]*D[j];
                P[i][j] = k;
              }
            
        }

        

        // int j = i - digonal; // M[i][i] 케이스도 포함시킴. 실수할 수 있으니
        // // 1 부터 시작함. 
        
        // int mink = 0;
        // for (int k = i; k <= j-1 ; k++) // !
        // {
        //     int cost = M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j];
        //     if (cost < M[i][j]) {
        //         M[i][j] = cost;
        //         P[i][j] = k; // Store k for reconstruction
        //     }
        // }
        
    }
}
    
void printMatrix(matrix& D, int n){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(D[i][j] == INF) continue;
            cout << D[i][j];
            if(j == n) cout << "\n";
            else cout << " ";
        }
    }
}



void printPath(matrix& P, int s, int e){

  cout << "(";
  if(s == e) {
    cout << "A" << s << ")";
    return;
  }

  int k = P[s][e];
  printPath(P, s, k);
  printPath(P, k+1, e);
  cout << ")";
}
  
int main(){

    int n;

    cin >> n;

    vector<int> a(n+1);

    

    matrix M(n+1, vector<int>(n+1, INF));
    matrix P(n+1, vector<int>(n+1, INF));

    for(int i=0; i<=n;i++){
        cin >> a[i];
    }
    
    chainedMatrix(M,P,a,n);
    
    printMatrix(M, n);
    printMatrix(P, n);

    cout << M[1][n] << endl;
    printPath(P, 1, n);

}