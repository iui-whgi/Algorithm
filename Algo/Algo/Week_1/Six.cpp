
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Fibo(int n,vector<int>& memo, int*m) {

    (*m)++;

    if(n<=1){
        memo[n]=n;
        return n;
    }

    // if (memo[n] != -1){
    //     *m=1;
    //     return memo[n];
    // }
    
    // (*m)=(*m)+2;
    memo[n] = (Fibo(n-1, memo,m) + Fibo(n-2, memo,m))% 1000000;

    return memo[n];
}


int main() {

    int n;
    cin >> n;

    int m=0;
    
    vector<int> memo(n+1, -1);

    
    cout << Fibo(n, memo,&m) << endl;
    cout << m << endl;
    
    return 0;

}


// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int Fibo(int n,vector<int>& memo, int*m) {

//     if(n<=1){
//         *m=1;
//         memo[n]=n;
//         return n;
//     }

//     if (memo[n] != -1){
//         *m=1;
//         return memo[n];
//     }

//     (*m)=(*m)+2;
//     memo[n] = (Fibo(n-1, memo,m) + Fibo(n-2, memo,m))% 1000000;

//     return memo[n];
// }


// int main() {

//     int n;
//     cin >> n;

//     int m=2;
    
//     vector<int> memo(n+1, -1);

    
//     cout << Fibo(n, memo,&m) << endl;
//     cout << m << endl;
    
//     return 0;

// }

