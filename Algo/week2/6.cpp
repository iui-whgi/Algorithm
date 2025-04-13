#include <iostream>
#include <map>
using namespace std;

typedef long long int;
map<int, int> memo;

int coll_length(int n) {
    if (n == 1) return 1;
    if (memo.count(n)) return memo[n];

    if (n % 2 == 0)
        return memo[n] = 1 + coll_length(n / 2);
    else
        return memo[n] = 1 + coll_length(3 * n + 1);
}

void forprint(int n) {
    while (true) {
        cout << n << ' ';
        if (n == 1) break;
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
    }
    cout << '\n';
}


int main() {
    int n, m;
    cin >> n >> m;

    int start = min(n, m), end = max(n, m);
    int maxNum = start, maxLen = 0;

    for (int i = start; i <= end; i++) {
        int len = coll_length(i);
        if (len > maxLen) {
            maxLen = len;
            maxNum = i;
        }
    }

    cout << maxNum << ' ' << maxLen << '\n';
    forprint(maxNum);

    return 0;
}



