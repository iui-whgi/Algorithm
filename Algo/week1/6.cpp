#include <iostream>
using namespace std;

int call_count = 0;

int fib(int n) {
    call_count++;
    if (n == 0) return 0;
    if (n == 1) return 1;
    return (fib(n - 1) + fib(n - 2)) % 1000000;
}

int main() {
    int n;
    cin >> n;
    
    int result = fib(n);
    
    cout << result << endl;
    cout << call_count << endl;

    return 0;
}

