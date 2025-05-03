#include <iostream>
#include <algorithm>
#include <vector>
#define INF 0x7fffffff
using namespace std;
typedef pair<int, int> edge;
typedef vector<int> vec1d;
typedef vector<vec1d> vec2d;

int V, E;
int s, e, w;

void printNearest(vec1d &arr){
  for(int i=2; i<=V; i++)
    cout << arr[i] << (i != V ? " " : "\n");
}

void printEdges(vec2d &W, vector<edge> &F){
  for(int i=0; i<F.size(); i++){
    s = F[i].first;
    e = F[i].second;
    cout << s << " " << e << " " << W[s][e];
    if(i != F.size()-1) cout << "\n";
  }         
}                  
                                                        
void prim(vec2d &W, vector<edge> &F){

  // 1. 변수 선언 파트
  int vnear, min;
  vec1d nearest(V+1, 0);
  vec1d distance(V+1, 0);

  // 2. v1을 시작정점으로 설정 후 초기화
  for(int i=2; i<=V; i++){
    nearest[i] = 1;         
    distance[i] = W[1][i];
  }
  printNearest(nearest);

  // 3. solve it using prim
  for(int i=2; i<=V; i++){
    // 3-1. 가장 가까운 정점찾기
    min = INF;
    for(int j=2; j<=V; j++)
      if(0 <= distance[j] && distance[j] < min){
        min = distance[j];
        vnear = j;
      }
    // 3-2. 가장 가까운 정점을 추가
    F.push_back(make_pair(vnear, nearest[vnear]));
    distance[vnear] = -1;

    // 3-3. 추가된 정점을 반영하여 업데이트
    for(int j=2; j<=V; j++)
      if(distance[j] > W[j][vnear]){
        distance[j] = W[j][vnear];
        nearest[j] = vnear;
      }
    
    printNearest(nearest);
  }
}

int main(){

  cin >> V >> E;
  vector<edge> F;
  vec2d W(V+1 , vec1d(V+1, INF));
  for(int i=1; i<=V; i++) W[i][i] = 0;

  for(int i=0; i<E; i++){
    cin >> s >> e >> w;
    W[s][e] = W[e][s] = w;
  }

  prim(W, F);

  printEdges(W, F);

  return 0;
}
