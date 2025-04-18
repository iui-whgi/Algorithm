#include <iostream>
#include <vector>
#include <utility>
#define INF 999
using namespace std;
typedef vector<pair<int, int> > path;
typedef vector<int> vector1d;
typedef vector<vector1d> vector2d;

void printAll(vector2d& arr, int n){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++){
      cout << arr[i][j];
      if(j == n) cout << "\n";
      else cout << " ";
    }
  }
}

void floyd(vector2d& D, vector2d& P, int V){
  for(int k=1; k<=V; k++)
    for(int i=1; i<=V; i++)
      for(int j=1; j<=V; j++)
        if(D[i][k] + D[k][j] < D[i][j]){
          D[i][j] = D[i][k] + D[k][j];
          P[i][j] = k;
        }
}

void init(vector2d& arr, int V){
  for(int i=0; i<=V; i++){
    for(int j=0; j<=V; j++){
      if(i == j) arr[i][j] = 0;
      else arr[i][j] = INF;
    }
  }
}

void find(vector2d& P, int y, int x){
  if(P[y][x] == 0) return;
  find(P, y, P[y][x]);
  cout << P[y][x] << " ";
  find(P, P[y][x], x);
}

void printPath(vector2d& D, vector2d& P, path& paths, int V){
  
  for(int i=0; i<paths.size(); i++){
    int y = paths[i].first;
    int x = paths[i].second;
    if(D[y][x] == INF) cout << "NONE\n";
    else {
      cout << y << " ";
      find(P, y, x);
      cout << x << "\n";
    }
  }
}

int main(){

  path paths;
  vector2d W, D, P;
  int V, E, u, v, w, T;
  
  cin >> V >> E;
  D.resize(V+1, vector1d(V+1)); init(D, V);
  P.resize(V+1, vector1d(V+1));
  for(int i=0; i<E; i++){
    cin >> u >> v >> w;
    D[u][v] = w;
  }

  cin >> T;
  for(int i=0; i<T; i++){
    cin >> u >> v;
    paths.push_back(pair<int, int>(u, v));
  }

  floyd(D, P, V);

  printAll(D,V); 
  printAll(P,V); 
  printPath(D, P, paths, V);

  return 0;
}