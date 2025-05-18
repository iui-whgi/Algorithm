#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> zeckendorf_decomposition(long long n) {
    vector<long long> fib = {1, 1};
    while (fib[fib.size() - 1] + fib[fib.size() - 2] <= n) {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }

    
    fib.erase(fib.begin());

    vector<long long> result;
    long long remaining = n;
    
    int i = fib.size() - 1;
    while (i >= 0 && remaining > 0) {
        if (fib[i] <= remaining) {
            result.push_back(fib[i]);
            remaining -= fib[i];
            i -= 2;
        } else {
            i--;
        }
    }
    
    sort(result.begin(), result.end());
    
    return result;
}

int main() {
    // freopen("input3.txt", "r", stdin);
    
    long long n;
    cin >> n;
    
    vector<long long> decomposition = zeckendorf_decomposition(n);
    
    for (long long num : decomposition) {
        cout << num << endl;
    }
    
    return 0;
}
