#include <iostream>
#include <algorithm>
#include <vector>
#define INF 0x7fffffff
#define lint long long int 
using namespace std;
typedef pair<int, int> edge;
typedef vector<int> vec1d;
typedef vector<lint> vec1D;
typedef vector<vec1d> vec2d;

int V, E, n;
int s, e, w, t;

void printArr(vec2d &arr){
  cout << "printing ARR\n";
  for(int i=1; i<arr.size(); i++){
    for(int j=1; j<arr[0].size(); j++){
      cout << arr[i][j] << " ";
    }
    cout << "\n";
  }
}

void printTouch(vec1d &arr){
  for(int i=2; i<=V; i++)
    cout << arr[i] << (i != V ? " " : "\n");
}

void printEdges(vec2d &W, vector<edge> &F){
  for(int i=0; i<F.size(); i++){
    s = F[i].first;
    e = F[i].second;
    cout << s << " " << e << " " << W[s][e] << "\n";
  }
}

void printPath(int e, vec1d &path){
  if(e == 1) return;
  printPath(path[e], path);
  cout << path[e] << " ";
}

vec1d dijkstra(vec2d &W, vector<edge> &F){

  // 1. 변수 선언 파트
  lint vnear, min;
  vec1d touch(V+1, 0);
  vec1D length(V+1, 0);

  // 2. v1을 시작정점으로 설정 후 초기화
  for(int i=2; i<=V; i++){
    touch[i] = 1;         
    length[i] = W[1][i];
  }
  printTouch(touch);

  // 3. solve it using dijkstra
  for(int i=2; i<=V; i++){
    // 3-1. 가장 가까운 정점찾기
    min = INF;
    for(int j=2; j<=V; j++)
      if(0 <= length[j] && length[j] < min){
        min = length[j];
        vnear = j;
      }
    // 3-2. 가장 가까운 정점을 추가
    F.push_back(make_pair(touch[vnear], vnear));

    // 3-3. 추가된 정점을 반영하여 업데이트
    for(int j=2; j<=V; j++)
      if(length[j] > W[vnear][j] + length[vnear]){
        length[j] = W[vnear][j] + length[vnear];
        touch[j] = vnear;
      }
    
    length[vnear] = -1;
    printTouch(touch);
  }
  return touch;
}


int main(){

  cin >> V >> E;
  vector<edge> F;
  vec2d W(V+1 , vec1d(V+1, INF));
  for(int i=1; i<=V; i++) W[i][i] = 0;

  for(int i=0; i<E; i++){
    cin >> s >> e >> w;
    W[s][e] = w;
  }

  vec1d path = dijkstra(W, F);
  printEdges(W, F);

  cin >> n;
  for(int i=0; i<n; i++){
    cin >> t;
    printPath(t, path); 
    cout << t << (i != n-1 ? "\n" : "");
  }

  return 0;
}


