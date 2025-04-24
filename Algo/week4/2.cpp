




#include <iostream>
#include <vector>
#include <string>
using namespace std;


int cnt=0;
int threshold;

typedef vector<int> LargeInteger;

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



void cArry(LargeInteger &v)
{

    int carry = 0;
    for (int i = 0; i < v.size(); i++)
    {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] = v[i] % 10;
    }
    if (carry != 0)
        v.push_back(carry);
}

void Add(LargeInteger &a, LargeInteger &b, LargeInteger &c)
{
    int len = a.size() > b.size() ? a.size() : b.size();
    c.resize(len);
    for (int i = 0; i < len; i++)
    {
        if (i < a.size())
            c[i] += a[i];
        if (i < b.size())
            c[i] += b[i];
    }
    cArry(c);
}

void reMove(LargeInteger &v)
{
    while (true)
    {
        if (v.size() != 0 && v.back() == 0)
            v.pop_back();
        else
            return;
    }
}

void roundup(LargeInteger &v)
{

    int borrow = 0;
    for (int i = 0; i < v.size(); i++)
    {
        v[i] -= borrow;
        borrow = 0;
        if (v[i] < 0)
        {
            v[i] += 10;
            borrow = 1;
        }
    }

    reMove(v);
}


void lsub(LargeInteger &a, LargeInteger &b, LargeInteger &c)
{

    int len = a.size() > b.size() ? a.size() : b.size();
    c.resize(len);
    for (int i = 0; i < len; i++)
    {
        if (i < a.size())
            c[i] += a[i];
        if (i < b.size())
            c[i] -= b[i];
    }
    roundup(c);
}

void lmult(LargeInteger &a, LargeInteger &b, LargeInteger &c)
{   
    c.resize(a.size() + b.size() - 1); 
    for(int i=0; i<c.size(); i++) c[i] = 0;
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            c[i + j] += a[i] * b[j];
    cArry(c);
}

void print(LargeInteger &v)
{
    for (int i = v.size() - 1; i >= 0; i--)
    {
        cout << v[i];
      
    }
}

void div_by_exp(LargeInteger& a, int exp, LargeInteger& c){
    for(int i=exp; i<a.size(); i++)
        c.push_back(a[i]);
}

void rem_by_exp(LargeInteger& a, int exp, LargeInteger& c){
    if(a.size() == 0){
        c.resize(0);
    }
    else {
        for(int i=0; i < exp && i < a.size(); i++)
            c.push_back(a[i]);
        reMove(c);
    }
}

void mul_by_exp(LargeInteger& a, int exp, LargeInteger& c){
    if(a.size() == 0){
        c.resize(0);
    } else {
        c.resize(a.size() + exp);
        fill(c.begin(), c.end(), 0);
        copy(a.begin(), a.end(), c.begin() + exp);
    }
}

LargeInteger prod(LargeInteger& a, LargeInteger& b){

    cnt++;
    int m = a.size() > b.size() ? a.size() : b.size();
    int n = m / 2;

    LargeInteger x1, x2, y1, y2;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8, r;

    if(a.size() == 0 || b.size() == 0){
        r.resize(0);
    }
    else if(m <= threshold){
        lmult(a, b, r);
    }
    else {
        div_by_exp(a, n, x1);
        rem_by_exp(a, n, x2);
        div_by_exp(b, n, y1);
        rem_by_exp(b, n, y2);

        t1 = prod(x1, y1); mul_by_exp(t1, n * 2, t2);  
        t3 = prod(x1, y2); t4 = prod(x2, y1); Add(t3, t4, t5); mul_by_exp(t5, n, t6); 
        t7 = prod(x2, y2);  //t7
        Add(t2, t6, t8);
        Add(t8, t7, r);
    }
    return r;
}


int main()
{
    string a_str, b_str;
    
    cin >> threshold;
    cin >> a_str >> b_str;
    
    
    LargeInteger u = stringToLargeInteger(a_str);
    LargeInteger v = stringToLargeInteger(b_str);
    LargeInteger r;

    r = prod(u ,v);
    cout << cnt << "\n";
    print(r);
    return 0;
}