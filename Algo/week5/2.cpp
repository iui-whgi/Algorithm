#include <iostream>
#include <map>
#include <utility> 

using namespace std;

typedef unsigned long long longInteger;
map<pair<int, int>, longInteger> memo; 

int cnt = 0;

longInteger binom(int n, int k) {
    cnt++;
    if (k == 0 || k == n)
        return 1;

    pair<int, int> key = make_pair(n, k);
    if (memo.find(key) != memo.end())
        return memo[key];
    
    memo[key] = (binom(n - 1, k - 1) + binom(n - 1, k)) % 10007;
    return memo[key];
}

int main() {
    int n, k;
    
    cin >> n >> k;
    
    longInteger result = binom(n, k);
    
    cout << result << endl;
    cout << cnt << endl;
    
    return 0;
}

