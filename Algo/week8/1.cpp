// page.61 참고!
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main(){

  int n; cin >> n;
  vector<int> D(n+1, 0);      // deadline
  vector<int> profit(n+1, 0); // profit
  vector<int> S(1,0);         // feasible sequence

  for(int i=1; i<=n; i++) cin >> D[i];
  for(int i=1; i<=n; i++) cin >> profit[i];
  
  // initialize
  S.push_back(1);

  // Greedy
  for(int i=2; i<=n; i++){

    vector<int> T = S;

    int idx = 0;
    for(int t=T.size()-1; t>0; t--){
      if(D[T[t]] <= D[i]){
        idx = t;
        break;
      }
    }
      
    T.insert(T.begin() + idx + 1 , i);

    int feasible = 1;
    for(int t=1; t<T.size(); t++){
      if(D[T[t]] < t){
        feasible = 0;
        break;
      }
    }

    if(feasible) S = T;
  }

  int ans = 0;
  for(int i=1; i<S.size(); i++) ans += profit[S[i]];

  cout << ans << "\n";
  for(int i=1; i<S.size(); i++) cout << profit[S[i]] << (i != S.size()-1 ? " ": "");

  return 0;
}