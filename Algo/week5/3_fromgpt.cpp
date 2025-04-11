
#include <iostream>
#include <vector>
#include <utility>
#define INF 2000
using namespace std;
typedef vector<pair<int, int> > path;
typedef vector<int> vector1d;
typedef vector<vector1d> vector2d;



int floyd(vector2d &D, vector2d &P, int V){
  for(int k=1; k<=V; k++){
    for(int i=1; i<=V; i++){
      for(int j=1; j<=V; j++){
        if(D[i][j] > D[i][k] + D[k][j]){
          D[i][j] = D[i][k] + D[k][j];
          P[i][j] = k;
        }
      }
    }
  }
  return 0;
}

void printAll(vector2d &D, int V){
  for(int i=1; i<=V; i++){
    for(int j=1; j<=V; j++){
      if(D[i][j] == INF) cout << "INF ";
      else cout << D[i][j] << " ";
    }
    cout << endl;
  }
}

void printPath(vector2d &D, vector2d &P, path &paths, int V){
  for(int i=0; i<paths.size(); i++){
    int u = paths[i].first;
    int v = paths[i].second;
    if(D[u][v] == INF) cout << "NONE" << endl;
    else{
      vector<int> path;
      while(u != v){
        path.push_back(u);
        u = P[u][v];
      }
      path.push_back(v);
      for(int j=0; j<path.size(); j++){
        cout << path[j] << " ";
      }
      cout << endl;
    }
  }
}

int main(){

  path paths;
  vector2d W, D, P;
  int V, E, u, v, w, T;
  
  cin >> V >> E;
  D.resize(V+1, vector1d(V+1)); 
  
  for(int i=0; i<V+1; i++){
    for(int j=0; j<V+1; j++){
      if(i==j) D[i][j] = 0;
      else D[i][j] = INF;
    }
  }
  

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