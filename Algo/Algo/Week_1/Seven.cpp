#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void binsearch(int n, vector<int>& S, int x, int& location)
{
    int low,high,mid;
    low = 0; high = n;
    location =0;
    while(low<high && location ==0){
        mid = (low+high)/2;
        
        if(x == S[mid]){
            location = mid;
        }
        else if(x < S[mid]){
            high = mid;
        }
        else{
            low = mid+1;
        }
    }
}

int main(){
    int N,M;
    cin >> N >> M;
    
    vector<int> S(N);
    for(int i=0; i<N; i++){
        cin >> S[i];
    }

    

}