#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vector1d;
typedef vector<vector1d> vector2d;
#define INF 999999

void printMatrix(vector2d& arr, int n){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      if(arr[i][j] == INF) continue;
      cout << arr[i][j];
      if(j == n) cout << "\n";
      else cout << " ";
    }
  }
}

void printPath(vector2d& P, int s, int e){

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

int main()
{
  int n;
  cin >> n;
  vector1d D(n+1,0);  // 연쇄행렬곱에서 필요한 행값, 열값만 모아둔 배열
  vector2d M(n+1, vector1d(n+1, INF));  // M[i][j] == 행렬i에서 행렬j까지 연쇄곱셈의 최소값
  vector2d P(n+1, vector1d(n+1, INF));  // 무엇을 곱했는지 기록..!

  for(int i=0; i<=n; i++)
    cin >> D[i];

  for(int i=0; i<=n; i++)
    M[i][i] = P[i][i] = 0; // no need to multiple itself. (Ai * Ai)

  for(int gap = 1; gap < n; gap++){
    for(int i = 1; i <= n - gap; i++){ // i doesn't start at 0 (i and j means "ith" matrix)
      int j = i + gap;
      for(int k=i; k<j; k++)
      if(M[i][j] > M[i][k] + M[k+1][j] + D[i-1]*D[k]*D[j]){
        M[i][j] = M[i][k] + M[k+1][j] + D[i-1]*D[k]*D[j];
        P[i][j] = k;
      }
    }
  }

  printMatrix(M, n);
  printMatrix(P, n);
  cout << M[1][n] << "\n";
  printPath(P, 1, n);

  return 0;
}