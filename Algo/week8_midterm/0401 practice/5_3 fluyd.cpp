

#include <iostream>
#include <vector>
#include <utility>
#define INF 999
using namespace std;
typedef vector<pair<int, int> > path;
typedef vector<int> vector1d;
typedef vector<vector1d> vector2d;












int main(){

  freopen("5_3 fluydInput.txt", "r", stdin); 

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
  

  // ! 아래 지금은 필요없다 . 나중에 print 할 때 사용용
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

