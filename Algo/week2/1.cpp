

#include <bits/stdc++.h>
using namespace std;

typedef long long long_t;

long_t fun(long_t n) {
    long_t i, j, cnt = 0;
    // for (i=1; i<=4*n; i+=2) // 2n times
    //     for (j=n; j>=1; j--) // n times
    //         cnt++;
    return 2*n*n;
}

int main() {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
}