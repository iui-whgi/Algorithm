



#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

map<int, int> memo;

int cnt;

int collatz(int n){

    cnt ++;
    if(n==1) return 1;
    if(memo.count(n)) return memo[n];
    else if(n%2 == 0){
        return memo[n] = 1 + collatz(n/2);
    }
    else if(n%2 == 1){
        return memo[n] = 1 + collatz(3*n+1);
    }
    
}



int collatz_find(int n, int m){
    
    int maxlen = 0, maxkey = 0;
    for (int i = n; i <= m; i++)
    {
        cnt = 0;
        collatz(i);

        // cout << cnt <<endl;
        
        
        if(memo[i] > maxlen){
            maxlen = memo[i];
            maxkey = i;
        }
        
    }
    
    return maxkey;
    

}



int main(){

    int n,m;

    cin >> n >> m;


    int max = collatz_find(n,m);

    cout << max ;

}