#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
typedef vector<int> LargeInteger;
int cnt = 0;

int n;

LargeInteger intToLargeInteger(int num) {
    if (num == 0) return {0};
    
    LargeInteger result;
    while (num > 0) {
        result.push_back(num % 10);
        num /= 10;
    }
    return result;
}

void lmult(LargeInteger u, LargeInteger v, LargeInteger &r) {
    int n = u.size();
    int m = v.size();
    r.resize(n + m, 0);
    
    for (int i = 0; i < n; i++) {
        int carry = 0;
        for (int j = 0; j < m; j++) {
            int prod = r[i + j] + u[i] * v[j] + carry;
            r[i + j] = prod % 10;
            carry = prod / 10;
        }
        if (carry > 0) {
            r[i + m] += carry;
        }
    }
    
    while (r.size() > 1 && r.back() == 0) {
        r.pop_back();
    }
}

void pow_by_exp(LargeInteger u, int m, LargeInteger &r) {
    r = u;
    r.insert(r.begin(), m, 0);
}

void div_by_exp(LargeInteger u, int m, LargeInteger &r) {
    if (u.size() <= m) {
        r.resize(1, 0);
    } else {
        r.resize(u.size() - m);
        for (int i = 0; i < r.size(); i++) {
            r[i] = u[i + m];
        }
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &r) {
    if (u.size() <= m) {
        r = u;
    } else {
        r.resize(m);
        for (int i = 0; i < m; i++) {
            r[i] = u[i];
        }
    }
}

void ladd(LargeInteger u, LargeInteger v, LargeInteger &r) {
    int n = max(u.size(), v.size());
    r.resize(n + 1, 0);
    
    int carry = 0;
    for (int i = 0; i < n; i++) {
        int sum = carry;
        if (i < u.size()) sum += u[i];
        if (i < v.size()) sum += v[i];
        
        r[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        r[n] = carry;
    } else {
        r.resize(n);
    }
} 

void prod(LargeInteger u, LargeInteger v, LargeInteger &r) {
    cnt++;
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    int n = max(u.size(), v.size());
    
    if (u.size() == 0 || v.size() == 0) {
        r.resize(1, 0);
        return;
    } else if (n <= ::n) {
        lmult(u, v, r);
    } else {
        int m = n / 2; 
        div_by_exp(u, m, x); rem_by_exp(u, m, y);
        div_by_exp(v, m, w); rem_by_exp(v, m, z);
        prod(x, w, t1); pow_by_exp(t1, 2 * m, t2);
        prod(x, z, t3); prod(w, y, t4); ladd(t3, t4, t5); pow_by_exp(t5, m, t6);
        prod(y, z, t7); ladd(t2, t6, t8); ladd(t8, t7, r);
    }
}

int main() {
    int a, b;
    
    cin >> n;
    cin >> a >> b;
    
    LargeInteger u = intToLargeInteger(a);
    LargeInteger v = intToLargeInteger(b);
    LargeInteger r;

    prod(u, v, r);

    cout << cnt << endl;

    cout << r[r.size()-1];
    for (int i = r.size() - 2; i >= 0; i--) {
        cout << r[i];
    }
    cout << endl;
    
    return 0;
}
