#include <iostream>
#include <vector>
#include <string>

using namespace std;
typedef vector<int> LargeInteger;
int cnt = 0;

int n;

// 문자열에서 LargeInteger로 변환 (최하위 자릿수부터 저장)
LargeInteger stringToLargeInteger(const string& s) {
    LargeInteger result;
    for (int i = s.length() - 1; i >= 0; i--) {
        result.push_back(s[i] - '0');
    }
    // 빈 벡터는 0을 나타내도록 함
    if (result.empty()) {
        result.push_back(0);
    }
    return result;
}

void lmult(LargeInteger u, LargeInteger v, LargeInteger &r) {
    int n = u.size();
    int m = v.size();
    r.resize(n + m, 0);  // 0으로 초기화
    
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
    
    // 앞의 0 제거
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
        // m보다 자릿수가 적으면 결과는 0
        r.resize(1, 0);
    } else {
        // m개의 하위 자릿수를 제외한 모든 자릿수 복사
        r.resize(u.size() - m);
        for (int i = 0; i < r.size(); i++) {
            r[i] = u[i + m];
        }
    }
}

void rem_by_exp(LargeInteger u, int m, LargeInteger &r) {
    if (u.size() <= m) {
        // 자릿수가 m보다 적으면 그 자체가 나머지
        r = u;
    } else {
        // 하위 m개의 자릿수만 가져옴
        r.resize(m);
        for (int i = 0; i < m; i++) {
            r[i] = u[i];
        }
    }
}

void ladd(LargeInteger u, LargeInteger v, LargeInteger &r) {
    int max_size = max(u.size(), v.size());
    r.resize(max_size + 1, 0);  // 캐리를 위한 추가 공간, 0으로 초기화
    
    int carry = 0;
    for (int i = 0; i < max_size; i++) {
        int sum = carry;
        if (i < u.size()) sum += u[i];
        if (i < v.size()) sum += v[i];
        
        r[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        r[max_size] = carry;
    } else {
        r.resize(max_size);
    }
}

void prod(LargeInteger u, LargeInteger v, LargeInteger &r) {
    cnt++; // prod 함수에서만 cnt 증가
    
    int max_size = max(u.size(), v.size());
    
    // 둘 중 하나라도 0이면 결과는 0
    if ((u.size() == 1 && u[0] == 0) || (v.size() == 1 && v[0] == 0)) {
        r.resize(1, 0);
        return;
    }
    
    // 기저 사례: n보다 작거나 같은 크기라면 일반 곱셈 사용
    if (max_size <= ::n) {
        lmult(u, v, r);
        return;
    }
    
    // Karatsuba 알고리즘 적용
    int m = max_size / 2;
    
    LargeInteger x, y, w, z;
    div_by_exp(u, m, x); rem_by_exp(u, m, y);
    div_by_exp(v, m, w); rem_by_exp(v, m, z);
    
    // t1 = x·w
    LargeInteger t1;
    prod(x, w, t1);
    
    // t2 = t1·10^(2m)
    LargeInteger t2;
    pow_by_exp(t1, 2 * m, t2);
    
    // t3 = x·z
    LargeInteger t3;
    prod(x, z, t3);
    
    // t4 = w·y
    LargeInteger t4;
    prod(w, y, t4);
    
    // t5 = t3 + t4
    LargeInteger t5;
    ladd(t3, t4, t5);
    
    // t6 = t5·10^m
    LargeInteger t6;
    pow_by_exp(t5, m, t6);
    
    // t7 = y·z
    LargeInteger t7;
    prod(y, z, t7);
    
    // t8 = t2 + t6
    LargeInteger t8;
    ladd(t2, t6, t8);
    
    // r = t8 + t7
    ladd(t8, t7, r);
}

int main() {
    int threshold;
    string a_str, b_str;
    
    cin >> threshold;
    cin >> a_str >> b_str;
    
    ::n = threshold;
    
    // 문자열을 LargeInteger로 변환
    LargeInteger u = stringToLargeInteger(a_str);
    LargeInteger v = stringToLargeInteger(b_str);
    LargeInteger r;
    
    // 연산 전 cnt 초기화
    cnt = 0;
    
    prod(u, v, r);
    
    cout << cnt << endl;
    
    // 결과 출력 (최상위 자릿수부터)
    // 앞의 0은 출력하지 않음
    bool leading_zero = true;
    cout << r[r.size()-1];
    for (int i = r.size() - 2; i >= 0; i--) {
        if (r[i] != 0) {
            leading_zero = false;
        }
        if (!leading_zero) {
            cout << r[i];
        }
    }
    // 모든 숫자가 0인 경우 0 하나만 출력
    if (leading_zero) {
        cout << "0";
    }
    cout << endl;
    
    return 0;
}