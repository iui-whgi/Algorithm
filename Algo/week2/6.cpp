#include <iostream>
#include <unordered_map>
using namespace std;

typedef long long ll;
unordered_map<ll, int> memo;

int coll_length(ll n) {
    if (n == 1) return 1;
    if (memo.count(n)) return memo[n];

    if (n % 2 == 0)
        return memo[n] = 1 + coll_length(n / 2);
    else
        return memo[n] = 1 + coll_length(3 * n + 1);
}

void forprint(ll n) {
    while (true) {
        cout << n << ' ';
        if (n == 1) break;
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
    }
    cout << '\n';
}

int main() {
    ll n, m;
    cin >> n >> m;

    ll start = min(n, m), end = max(n, m);
    ll maxNum = start, maxLen = 0;

    for (ll i = start; i <= end; i++) {
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
