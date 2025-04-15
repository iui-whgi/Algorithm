

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){

  int n;
  cin >> n;

  int s, e;
  vector<pair<int, int> > v1, v2;
  for(int i=0; i<n; i++){
    cin >> s >> e;
    v1.push_back(make_pair(s,e));
  }

  v2.push_back(make_pair(v1[0].first, v1[0].second));
  e = v2[0].second;
  for(int i=1; i<n; i++){
    if(e <= v1[i].first){
      e = v1[i].second;
      v2.push_back(make_pair(v1[i].first, v1[i].second));
    }
  }

  cout << v2.size() << "\n";
  for(int i=0; i<v2.size(); i++){
    s = v2[i].first;
    e = v2[i].second;
    cout << s << " " << e << (i != v2.size()-1 ? "\n" : "");
  }

  return 0;
}