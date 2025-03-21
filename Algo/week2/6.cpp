// #include <iostream>
// #include <bits/stdc++.h>
// typedef long long long_t;
// using namespace std;

// int result = 0;

// int collatz(long_t n , long_t *count){
//     (*count)++;
//     cout << n << endl;
//     if(n == 1){
//         // cout << n << endl;
//         return 1;
//     }
//     else {
//         if(n % 2 == 0){
//         // cout << n / 2 << endl;
//         // if(n / 2 == 1){
//         //     return 1;
//         // }
//         return collatz(n / 2, count);
//         }
//         else 
//             // cout << 3 * n + 1 << endl;
//             // if(3 * n + 1 == 1){
//             //     return 1;
//             // 
//             return collatz(3 * n + 1, count);
        
        
//     }
    
// }

// int main(){
//     long_t n,m, count = 0;
//     cin >> n >> m;

//     long_t max_i = 0;
//     long_t max = 0;
    
//     for (size_t i = n; i <= m; i++)
//     {
//         count = 0;
//         collatz(i, &count);
//         if(count > max)
//         {
//             max_i = i;
//             max = count;
//         }
       
//     }
//     collatz(max_i, &count);
//     // cout << max_i << " " << count << endl;

//     return 0;
// }


#include <iostream>
#include <vector>
typedef long long long_t;
using namespace std;

// 콜라츠 수열 계산 (출력 없이)
int coll_length(long_t n, long_t *count) {
    (*count)++;
    if (n == 1) {
        return 1;
    }
    else {
        if (n % 2 == 0) {
            return coll_length(n / 2, count);
        }
        else {
            return coll_length(3 * n + 1, count);
        }
    }
}

// 콜라츠 수열 생성 및 출력
void forprint(long_t n) {
    cout << n << " ";
    if (n == 1) {
        return;
    }
    else if (n % 2 == 0) {
        forprint(n / 2);
    }
    else {
        forprint(3 * n + 1);
    }
}

int main() {
    long_t n, m, count = 0;
    cin >> n >> m;

    long_t max_i = 0;
    long_t max = 0;
    
    // n부터 m까지 각 숫자에 대해 콜라츠 수열 길이 확인
    for (size_t i = n; i <= m; i++) {
        count = 0;
        coll_length(i, &count);
        if (count >= max) {
            max_i = i;
            max = count;
        }
    }
    
    // 결과 출력
    cout << max_i << " " << max-1 << endl;
    forprint(max_i);
    cout << endl;

    return 0;
}