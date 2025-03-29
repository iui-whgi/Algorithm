#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
typedef vector<int> LargeInteger;
int cnt = 0;

int n;

void lmult(LargeInteger u, LargeInteger v, LargeInteger &r) {
    int n = u.size();
    int m = v.size();
    r.resize(n + m, 0);  // Initialize with zeros
    
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
    
    // Remove leading zeros
    while (r.size() > 1 && r.back() == 0) {
        r.pop_back();
    }
    
    cnt++;  // Increment operation counter
}
void pow_by_exp(LargeInteger u, int m , LargeInteger &r){
    r = u;
    r.insert(r.begin(), m ,0);
    cnt++;
}

void div_by_exp(LargeInteger u, int m, LargeInteger &r) {
    if (u.size() <= m) {
        // If we're removing more digits than exist, result is 0
        r.resize(0);
    } else {
        // Copy all digits except the m least significant ones
        r.resize(u.size() - m);
        for (int i = 0; i < r.size(); i++) {
            r[i] = u[i + m];
        }
    }
    cnt++;  // Increment operation counter
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &r) {
    if (u.size() <= m) {
        // If number has fewer than m digits, it is its own remainder
        r = u;
    } else {
        // Take only the m least significant digits
        r.resize(m);
        for (int i = 0; i < m; i++) {
            r[i] = u[i];
        }
    }
    cnt++;  // Increment operation counter
}

void ladd(LargeInteger u, LargeInteger v, LargeInteger &r) {
    int n = max(u.size(), v.size());
    r.resize(n + 1);  // Extra space for potential carry
    
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
    
    cnt++; 
} 
void prod(LargeInteger u, LargeInteger v, LargeInteger &r) {
    cnt++;
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    int n = max(u.size(), v.size());
    if (u.size() == 0 || v.size() == 0) // LargeInteger 하나라도 0이라면 r은 0으로 초기화해준다.
        r.resize(0);
    else if (n <= n)
        lmult(u, v, r);
    else {
        int m = n / 2; 
        div_by_exp(u, m, x); rem_by_exp(u, m, y);
        div_by_exp(v, m, w); rem_by_exp(v, m, z);
        // t2 <- prod(x,w) * 10^(2*m)
        prod(x, w, t1); pow_by_exp(t1, 2 * m, t2);
        // t6 <- (prod(x,z)+prod(w,y)) * 10^m
        prod(x, z, t3); prod(w, y, t4); ladd(t3, t4, t5); pow_by_exp(t5, m, t6);
        // r <- t2 + t6 + prod(y, z)
        prod(y, z, t7); ladd(t2, t6, t8); ladd(t8, t7, r);
    }
}

int main(){
    int a, b ;

    
    cin >> n;
    cin >> a;
    cin >> b;
    
    LargeInteger u(a), v(b), r; // a개의 0으로 초기화됨, r은 초기화 하지 않은 상태 


    prod(u, v, r); 

    cout << cnt << endl;;

    cout << r[0];
    for(int i = 1; i< r.size(); i++){
        cout << " " << r[i];
    }
    

    
}