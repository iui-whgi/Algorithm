#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define INF 0x7fffffff
using namespace std;
typedef pair<int, int> pii;
typedef priority_queue<pair<int, pii> > PriorityQueue;
typedef vector<int> vec1d;
typedef vector<vec1d> vec2d;

int V, E;
int s, e, w;
int parent[100001] = {0};

void InitUF(){
  for(int i=0; i<=V; i++) parent[i] = i;
}

int getParent(int a){
  if(parent[a] == a) return a;
  else return parent[a] = getParent(parent[a]);
}

int Find(int a, int b){
  a = getParent(a);
  b = getParent(b);
  return a == b;
}

void Union(int a, int b){
  a = getParent(a);
  b = getParent(b);
  if(a < b) parent[b] = a;
  else parent[a] = b;
}

void printEdges(vec2d &W, vector<pii> &F){
  for(int i=0; i<F.size(); i++){
    s = F[i].first;
    e = F[i].second;
    cout << s << " " << e << " " << W[s][e];
    if(i != F.size()-1) cout << "\n";
  }
}
void kruskal(vec2d &W, vector<pii> &F){
  InitUF();
  PriorityQueue pq;
  for(int i=1; i<=V; i++)
    for(int j=1; j<=V; j++)
      if(W[i][j] != INF && W[i][j] != 0)
        pq.push(make_pair(-W[i][j], make_pair(i, j)));
  
  int s, e, ps, pe;
  while(!pq.empty()){
    s = pq.top().second.first;
    e = pq.top().second.second; 
    ps = getParent(s);
    pe = getParent(e);
    if(ps != pe){
      Union(ps, pe);
      F.push_back(pq.top().second);
    }
    pq.pop();
  }
}

int main(){

  cin >> V >> E;
  vector<pii> F;
  vec2d W(V+1 , vec1d(V+1, INF));
  for(int i=1; i<=V; i++) W[i][i] = 0;

  for(int i=0; i<E; i++){
    cin >> s >> e >> w;
    W[s][e] =  w;
  }

  kruskal(W, F);

  printEdges(W, F);

  return 0;
}