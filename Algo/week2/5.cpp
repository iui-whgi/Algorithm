
#include <iostream>
#include <bits/stdc++.h>
typedef long long long_t;
using namespace std;

int result = 0;

int collatz(long_t n){
    cout << n << endl;
    if(n == 1){
        // cout << n << endl;
        return 1;
    }
    else {
        if(n % 2 == 0){
        // cout << n / 2 << endl;
        // if(n / 2 == 1){
        //     return 1;
        // }
        return collatz(n / 2);
        }
        else 
            // cout << 3 * n + 1 << endl;
            // if(3 * n + 1 == 1){
            //     return 1;
            // 
            return collatz(3 * n + 1);
        
        
    }
    
}

int main(){
    long_t n;
    cin >> n;
    collatz(n);
    return 0;
}

