#include <iostream>
#include <vector>
#define INF 0x7fffffff
using namespace std;
typedef struct vector<long long int> vec1d;
typedef struct vector<vec1d> vec2d;

int n;

void input(vec1d &P, vec1d &T){
  for (int i = 1; i <= n; i++)
    cin >> T[i];
  for (int i = 1; i <= n; i++)
    cin >> P[i];
}

void printArr(vec2d &arr){
  for (int i = 1; i <= n+1; i++){
    cout << "0";
    for (int j = i; j <= n; j++){
      cout << " " << arr[i][j];
      if (j == n) cout << "\n";
    }
  }
}

void optimalBST(vec1d &P, vec1d &T, vec2d &A, vec2d &R){

  for (int i = 1; i <= n; i++){
    A[i][i] = P[i];
    A[i][i - 1] = A[i + 1][i] = 0;
    R[i][i] = i;
  }

  for (int gap = 1; gap < n; gap++) {
    for (int i = 1; i <= n - gap; i++) {
      int j = i + gap, pSum = 0;
      for (int k = i; k <= j; k++) pSum += P[k];
      for (int k = i; k <= j; k++)
        if (A[i][j] > A[i][k - 1] + A[k + 1][j] + pSum) {
          A[i][j] = A[i][k - 1] + A[k + 1][j] + pSum;
          R[i][j] = k;
        }
    }
  }
}

void preorder(vec1d &T, vec2d &R, int l, int r)
{
  static int cnt = 0;
  if(l > r) return;
  int v = R[l][r];
  cout << T[v]; if(++cnt != n) cout << " ";
  preorder(T, R, l, v-1);
  preorder(T, R, v+1, r);
}

void inorder(vec1d &T, vec2d &R, int l, int r)
{
  static int cnt = 0;
  if(l > r) return;
  int v = R[l][r];
  inorder(T, R, l, v-1);
  cout << T[v]; if(++cnt != n) cout << " ";
  inorder(T, R, v+1, r);
}

int main()
{
  cin >> n;

  vec1d P(n + 1, 0);
  vec1d T(n + 1, 0);
  vec2d A(n + 2, vec1d(n + 2, INF));
  vec2d R(n + 2, vec1d(n + 2, 0));

  input(P, T);

  optimalBST(P, T, A, R);

  printArr(A); cout << "\n";
  printArr(R); cout << "\n";
  cout << A[1][n] << "\n";

  preorder(T, R, 1, n); cout << "\n";
  inorder(T, R, 1, n); cout << "\n";

  return 0;
}