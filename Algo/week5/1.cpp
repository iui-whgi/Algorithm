
#include <iostream>
#include <vector>
#include <algorithm>   
#include <string>

using namespace std;


typedef unsigned long long longInteger;



longInteger bin2(int n , int k){

    vector<longInteger> B(k+1,0);


    
    B[0]= 1;
    for (int i = 0; i <= n; i++)
    {   
        for (int j = min(i,k); j > 0; j--)
        {
            
            B[j] = (B[j] + B[j-1])%10007;
                
        }
        
    }
    return B[k];

    
}


int main(){
    
    int n,k;

    cin >> n >> k;

    longInteger result = bin2(n,k);

    cout << result <<endl;
}