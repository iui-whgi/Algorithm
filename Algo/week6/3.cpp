#include <iostream>
#include <vector>
#include <string>
#define INF 0x7fffffff
using namespace std;
typedef vector<vector<int> > matrix;

void lcs(string &X, string &Y, matrix &DP, matrix &P){
  for(int i=1; i<X.length(); i++){
    for(int j=1; j<Y.length(); j++){
      DP[i][j] = X[i] == Y[j] ? DP[i - 1][j - 1] + 1 : DP[i][j - 1] > DP[i - 1][j] ? DP[i][j - 1] : DP[i - 1][j];
			P[i][j] = X[i] == Y[j] ? 1 : DP[i][j - 1] > DP[i - 1][j] ? 2 : 3;
    }
  }
}

void printPath(matrix &P, int i, int j, string X){
  if(i == 0 || j == 0) return;

  if(P[i][j] == 1){
    printPath(P, i-1, j-1, X);
    cout << X[i];
  }
  else if(P[i][j] == 2){
    printPath(P, i, j-1, X);
  }
  else if(P[i][j] == 3){
    printPath(P, i-1, j, X);
  }
}

int main(){

  string X, Y;

  cin >> X; X.insert(0, " ");
  cin >> Y; Y.insert(0, " ");

  matrix DP(X.length()+1, vector<int>(Y.length()+1, 0));
  matrix P(X.length()+1, vector<int>(Y.length()+1, 0));

  lcs(X, Y, DP, P);

  cout << DP[X.length()-1][Y.length()-1] << "\n";
  printPath(P, X.length()-1, Y.length()-1, X);

  return 0;
}